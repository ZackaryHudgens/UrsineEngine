#include "CallbackHolder.hpp"

using gCore::CallbackHolder;

int CallbackHolder::mIdCounter = 0;
std::vector<int> CallbackHolder::mAvailableIds;

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
 * and places the ID into the vector of available IDs.
 */
CallbackHolder::~CallbackHolder()
{
  for(auto& cb : mCallbacks)
  {
    cb->Disconnect(mId);
  }

  mAvailableIds.emplace_back(mId);
}

/**
 * Adds the given callback to this container, and connects
 * the callback's temporary function to this container's ID.
 *
 * @param aCallback The callback to add to this container.
 */
void CallbackHolder::Add(CallbackBase* aCallback)
{
  aCallback->ConnectTempToId(mId);
  mCallbacks.emplace_back(aCallback);
}
