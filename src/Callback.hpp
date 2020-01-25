#ifndef CALLBACK_HPP
#define CALLBACK_HPP

#include <functional>
#include <vector>

#include <iostream>

namespace gCore
{
  class CallbackBase
  {
    public:
      CallbackBase();

      // Clear() empties mConnectedFunctions;
      // a Disconnect() function should be implemented,
      // but I don't know how to parameterize it.
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

      void Notify(Args... args)
      {
        for(auto& func : mConnectedFunctions)
        {
          func(args...);
        }
      }

      CallbackBase* Connect(const std::function<void(Args...)>& aFunction)
      {
        mConnectedFunctions.emplace_back(aFunction);
        return this;
      }

    private:
      std::vector<std::function<void(Args...)>> mConnectedFunctions;
  };
}

#endif
