#ifndef COREOBSERVERS_HPP
#define COREOBSERVERS_HPP

#include "Signal.hpp"

/**
 * Type Definitions for core signals.
 */
namespace signals
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
}

/**
 * Declarations of core signals.
 */
namespace core
{
  /**
   * Input Signals
   */
  signals::KeyPressedSignal         KeyPressed;
  signals::KeyReleasedSignal        KeyReleased;
  signals::MouseMovedSignal         MouseMoved;
  signals::MouseEnteredOrLeftSignal MouseEnteredOrLeft;
  signals::MouseButtonPressedSignal MouseButtonPressed;
  signals::MouseScrolledSignal      MouseScrolled;
}

#endif
