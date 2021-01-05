#ifndef CORESIGNALS_HPP
#define CORESIGNALS_HPP

#include "Signal.hpp"

/**
 * A selection of signals that come in handy throughout the core
 * engine. Instances of each are created in CoreSignals.cpp..
 */
namespace core
{
  /**
   * Input Signals
   */
  typedef core::SignalT<int, int, int>  KeyPressedSignal;
  typedef core::SignalT<int, int, int>  KeyReleasedSignal;
  typedef core::SignalT<double, double> MouseMovedSignal;
  typedef core::SignalT<bool>           MouseEnteredOrLeftSignal;
  typedef core::SignalT<int, int, int>  MouseButtonPressedSignal;
  typedef core::SignalT<double, double> MouseScrolledSignal;

  extern KeyPressedSignal         KeyPressed;
  extern KeyReleasedSignal        KeyReleased;
  extern MouseMovedSignal         MouseMoved;
  extern MouseEnteredOrLeftSignal MouseEnteredOrLeft;
  extern MouseButtonPressedSignal MouseButtonPressed;
  extern MouseScrolledSignal      MouseScrolled;
}

#endif
