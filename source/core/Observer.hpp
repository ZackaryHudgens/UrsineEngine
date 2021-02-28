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
      Observer();
      ~Observer();

      void Add(Signal* aSignal);

    private:
      std::vector<Signal*> mConnectedSignals;
  };
}

#endif
