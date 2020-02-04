#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <functional>
#include <map>
#include <vector>

#include <iostream>

namespace gCore
{
  /**
   * A base Callback class that doesn't need templates.
   * Contains two pure virtual functions that are implemented
   * by the Callback implementation.
   */
  class CallbackBase
  {
    public:
      CallbackBase() {};

      virtual void Disconnect(int aId) = 0;
      virtual void Clear() = 0;
  };

  /**
   * A Callback is an object that holds a list of functions.
   * Functions are added to the Callback via the Connect function.
   * Whenever Notify() is called, all the attached functions
   * will be called as well.
   */
  template <typename ...Args>
  class Callback : public CallbackBase
  {
    public:
      Callback() {};

      /**
       * Calls each function in mFunctionMap.
       *
       * @param args The arguments associated with this Callback.
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
       * Connects a function to this callback. This is intended to be used
       * with the CallbackHolder class.
       *
       * @param aId The ID to be associated with this function.
       * @param aFunction A function to call when Notify is called.
       */
      CallbackBase* Connect(int aId, const std::function<void(Args...)>& aFunction)
      {
        if(mFunctionMap.find(aId) != mFunctionMap.end())
        {
          mFunctionMap.at(aId).emplace_back(aFunction);
        }
        else
        {
          std::vector<std::function<void(Args...)>> newList;
          newList.emplace_back(aFunction);
          mFunctionMap.emplace(aId, newList);
        }

        return this;
      }

      /**
       * Disconnects all functions represented by the given ID.
       *
       * @param aId The ID to remove.
       */
      void Disconnect(int aId) override
      {
        auto functionList = mFunctionMap.find(aId);
        if(functionList != mFunctionMap.end())
        {
          mFunctionMap.erase(functionList);
        }
      }

      /**
       * Disconnects all functions connected to this Callback.
       */
      void Clear() override
      {
        mFunctionMap.clear();
      }

    private:
      std::map<int, std::vector<std::function<void(Args...)>>> mFunctionMap;
  };
}

#endif
