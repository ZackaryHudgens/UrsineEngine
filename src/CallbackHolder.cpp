#include "CallbackHolder.hpp"

using gCore::CallbackHolder;

int CallbackHolder::mIdCounter = 0;

/**
 * Constructor for the CallbackHolder. Assigns an ID based on
 * the static counter variable.
 */
CallbackHolder::CallbackHolder()
{
  if(!mAvailableIds.empty())
  {
    mId = mAvailableIds.back();
    mAvailableIds.pop_back();
  }
  else
  {
    mId = mIdCounter;
    ++mIdCounter;
  }
}

/**
 * Destructor for the CallbackHolder. Disconnects each Callback,
 * and returns the ID to the vector of available IDs.
 */
CallbackHolder::~CallbackHolder()
{
  for(auto& cb : mCallbacks)
  {
    cb->Disconnect(mId);
  }
}
