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
   * Contains three pure virtual functions that are implemented
   * by the Callback implementation.
   */
  class CallbackBase
  {
    public:
      CallbackBase() {};

      virtual void ConnectTempToId(int aId) = 0;
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
       * Connects the stored temporary function to this callback using the
       * given ID. This is intended to be used with the CallbackHolder class.
       *
       * @param aId The ID to be associated with the temporary function.
       */
      void ConnectTempToId(int aId) override
      {
        if(mFunctionMap.find(aId) != mFunctionMap.end())
        {
          mFunctionMap.at(aId).emplace_back(mTempFunction);
        }
        else
        {
          std::vector<std::function<void(Args...)>> newList;
          newList.emplace_back(mTempFunction);
          mFunctionMap.emplace(aId, newList);
        }
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

      /**
       * Saves the given function in a member variable. The function
       * will be added to the function map on the next call to ConnectToId.
       *
       * @param aFunction The function to store temporarily.
       * @return A pointer to this object as a CallbackBase.
       */
      CallbackBase* Connect(const std::function<void(Args...)>& aFunction)
      {
        mTempFunction = aFunction;

        return this;
      }

    private:
      std::map<int, std::vector<std::function<void(Args...)>>> mFunctionMap;
      std::function<void(Args...)> mTempFunction;
  };
}

#endif
