#ifndef CALLBACKHOLDER_HPP
#define CALLBACKHOLDER_HPP

#include "Callback.hpp"

namespace gCore
{
  // Holds a list of CallbackBase and somehow notifies the callback
  // of being deleted (?)
  class CallbackHolder
  {
    public:
      CallbackHolder();
      ~CallbackHolder();

      void Add(CallbackBase* aCallback);
  };
}

#endif
