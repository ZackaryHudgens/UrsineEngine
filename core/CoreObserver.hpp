#ifndef COREOBSERVER_HPP
#define COREOBSERVER_HPP

#include "Callback.hpp"

namespace core
{
  /**
   * An Observer class that contains several static Callback objects
   * associated with the core operation of the engine.
   */
  class CoreObserver
  {
    public:
      CoreObserver() {}

      /**
       * Mouse & keyboard input callbacks.
       */
      typedef Callback<int, int> mouseMovedCallback;
      static mouseMovedCallback MouseMoved;

      typedef Callback<int, int> singleClickCallback;
      static singleClickCallback SingleClick;

      typedef Callback<int, int> doubleClickCallback;
      static doubleClickCallback DoubleClick;

      typedef Callback<int, int> mouseReleasedCallback;
      static mouseReleasedCallback MouseReleased;

      typedef Callback<int, int> mouseWheelCallback;
      static mouseWheelCallback MouseScroll;
  };
}

#endif
