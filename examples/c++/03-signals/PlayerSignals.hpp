#ifndef PLAYERSIGNALS_HPP
#define PLAYERSIGNALS_HPP

#include "PlayerObject.hpp"

#include "Signal.hpp"

/**
 * A collection of signals each involving a PlayerObject.
 *
 * Right now this only contains a single signal, but we'll expand
 * on this later.
 */
namespace example_three
{
  /**
   * First, create a type definition for your signal. This step isn't
   * strictly necessary, but it helps keep your code clean.
   *
   * Note that the template types correspond to the argument types
   * that will get passed to each connected function. These arguments
   * can be anything, but in this case, the only argument is a pointer
   * to a PlayerObject.
   */
  typedef core::SignalT<PlayerObject*> QPressedSignal;

  /**
   * Next, create references to the actual signals. The 'extern' keyword
   * tells the compiler that an instance of this variable exists somewhere
   * (in this case, it exists in PlayerSignals.cpp) without declaring it.
   *
   * Placing this here allows any code that includes this file to call the
   * signal's Notify function, and for any Observers to connect to it.
   */
  extern QPressedSignal QPressed;
}

#endif
