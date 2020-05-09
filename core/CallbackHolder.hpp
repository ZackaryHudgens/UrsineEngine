#ifndef CALLBACKHOLDER_HPP
#define CALLBACKHOLDER_HPP

#include "Callback.hpp"

namespace core
{
  /**
   * A helper class that maintains a list of Callbacks and disconnects
   * those Callbacks upon deletion.
   */
  class CallbackHolder
  {
    public:
      CallbackHolder();
      ~CallbackHolder();

      void Add(CallbackBase* aCallback);

    private:
      static int mIdCounter;
      static std::vector<int> mAvailableIds;
      int mId;

      std::vector<CallbackBase*> mCallbacks;
  };
}

#endif
