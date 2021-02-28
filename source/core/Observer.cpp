#include "Observer.hpp"

#include <algorithm>

#include "Signal.hpp"

using UrsineCore::Observer;
using UrsineCore::Signal;

Observer::Observer()
{
}

/**
 * The destructor for the Observer class disconnects itself
 * from each connected Signal; this way, when the Signal is
 * next notified, it won't be calling functions from an object
 * that no longer exists.
 */
Observer::~Observer()
{
  for(auto& s : mConnectedSignals)
  {
    s->Disconnect(*this);
  }
}

/**
 * Adds a Signal to keep track of, if it isn't already being tracked.
 *
 * @param aSignal The Signal to keep track of.
 */
void Observer::Add(Signal* aSignal)
{
  auto s = std::find(mConnectedSignals.begin(),
                     mConnectedSignals.end(),
                     aSignal);
  if(s == mConnectedSignals.end())
  {
    mConnectedSignals.emplace_back(aSignal);
  }
}
