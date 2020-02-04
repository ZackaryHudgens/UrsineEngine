#ifndef CALLBACKHOLDER_HPP
#define CALLBACKHOLDER_HPP

#include "Callback.hpp"

namespace gCore
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

      /**
       * Adds a Callback to this CallbackHolder.
       *
       * @param aCallback The Callback to add to this CallbackHolder.
       */
      void Add(CallbackBase* aCallback)
      {
        mCallbacks.emplace_back(aCallback);
      }

      /**
       * Returns the Id for this CallbackHolder.
       */
      int GetId() { return mId; }

    private:
      static int mIdCounter;
      int mId;
      std::vector<int> mAvailableIds;

      std::vector<CallbackBase*> mCallbacks;
  };
}

#endif
