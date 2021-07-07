#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <vector>

namespace UrsineCore
{
  class Signal;

  /**
   * An Observer acts as a base class for any other class that wants to use
   * Signals. All Observers automatically disconnect themselves from any
   * Signals when destroyed.
   */
  class Observer
  {
    public:

      /**
       * Constructor.
       */
      Observer();

      /**
       * Destructor. When destroyed, the Observer class disconnects itself
       * from each connected Signal; this way, when the Signal is
       * next notified, it won't be calling functions belonging to an object
       * that no longer exists.
       */
      ~Observer();

      /**
       * Adds a Signal to keep track of, if it isn't already being tracked.
       *
       * @param aSignal The Signal to keep track of.
       * @return True if successful, false otherwise.
       */
      bool Add(Signal* aSignal);

    private:
      std::vector<Signal*> mConnectedSignals;
  };
}

#endif
