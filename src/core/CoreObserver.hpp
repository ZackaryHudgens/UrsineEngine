#ifndef COREOBSERVER_HPP
#define COREOBSERVER_HPP

#include <SDL2/SDL.h>

#include "Animation.hpp"
#include "Callback.hpp"

using gCore::Animation;

namespace gCore
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

      typedef Callback<const SDL_Scancode&> keyPressedCallback;
      static keyPressedCallback KeyPressed;

      typedef Callback<const SDL_Scancode&> keyReleasedCallback;
      static keyReleasedCallback KeyReleased;

      /**
       * Controller input callbacks.
       */
      typedef Callback<const SDL_GameControllerButton&> buttonPressedCallback;
      static buttonPressedCallback ButtonPressed;

      typedef Callback<const SDL_GameControllerButton&> buttonReleasedCallback;
      static buttonReleasedCallback ButtonReleased;

      /**
       * Animation callbacks.
       */
      typedef Callback<const Animation&> animationAdvancedCallback;
      static animationAdvancedCallback AnimationAdvanced;
  };
}

#endif
