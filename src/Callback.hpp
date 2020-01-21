#ifndef CALLBACKHOLDER_HPP
#define CALLBACKHOLDER_HPP

#include <functional>
#include <vector>

#include <iostream>

namespace gCore
{
  /**
   * A Callback is an object that holds a list of functions.
   * Functions are added to the Callback via the Connect function.
   * Whenever Notify() is called, all the attached functions
   * will be called as well.
   */
  template <typename R, typename ...Args>
  class Callback
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

      void Connect(const std::function<R(Args...)>& aFunction)
      {
        mConnectedFunctions.emplace_back(aFunction);
      }

    private:
      std::vector<std::function<R(Args...)>> mConnectedFunctions;
  };
}

#endif
