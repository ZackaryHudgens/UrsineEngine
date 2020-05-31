#ifndef SIGNAL_HPP
#define SIGNAL_HPP

#include <functional>
#include <map>
#include <vector>

#include "Observer.hpp"

namespace core
{
  /**
   * A non-templated base class for Signals.
   *
   * This version is used by Observers to keep track
   * of which Signals they're connected to without needing to know exactly
   * what types the Signal accepts.
   */
  class Signal
  {
    public:
      virtual void Disconnect(Observer& aObserver) = 0;
  };

  /**
   * The "real" Signal class; the template types specify what argument types
   * this Signal needs.
   *
   * Signals contain a map of Observers to function pointers; when the Notify
   * function is called, each of the stored function pointers are also called.
   */
  template <typename ...Args>
  class SignalT : public Signal
  {
    public:

      /**
       * Calls each connected function.
       *
       * @param args The arguments passed to each connected function.
       */
      void Notify(Args... args)
      {
        for(auto& funcData : mFunctionMap)
        {
          for(auto& func : funcData.second)
          {
            func(args...);
          }
        }
      }

      /**
       * Connects a function to this Signal and associates it with the
       * given Observer.
       *
       * @param aObserver The Observer associated with this function.
       * @param aFunction The function to connect.
       */
      void Connect(Observer& aObserver,
                   const std::function<void(Args...)>& aFunction)
      {
        auto funcList = mFunctionMap.find(&aObserver);
        if(funcList != mFunctionMap.end())
        {
          funcList.second.emplace_back(aFunction);
        }
        else
        {
          std::vector<std::function<void(Args...)>> newList;
          newList.emplace_back(aFunction);
          mFunctionMap.emplace(&aObserver, newList);
        }

        aObserver.Add(this);
      }

      /**
       * Disconnects all functions associated with the given Observer.
       *
       * @param aObserver The Observer to disconnect.
       */
      void Disconnect(Observer& aObserver) override
      {
        auto funcList = mFunctionMap.find(&aObserver);
        if(funcList != mFunctionMap.end())
        {
          mFunctionMap.erase(funcList);
        }
      }

    private:
      std::map<Observer*, std::vector<std::function<void (Args...)>>> mFunctionMap;
  };
}

#endif
