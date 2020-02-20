#include "CallbackHolder.hpp"
#include "Component.hpp"
#include "Environment.hpp"

namespace gCore
{
  /**
   * A Component that contains several functions that are hooked up
   * to input callbacks. These functions are virtual and should be
   * implemented by child classes to define behavior.
   */
  class InputComponent : public Component
  {
    public:
      InputComponent();

      virtual void Update() override {}

      virtual void MouseMoved(int aX, int aY) {}
      virtual void SingleClick(int aX, int aY) {}
      virtual void DoubleClick(int aX, int aY) {}
      virtual void MouseReleased(int aX, int aY) {}
      virtual void MouseScroll(int aHorz, int aVert) {}

      virtual void KeyPressed(const SDL_Scancode& aKey) {}
      virtual void KeyReleased(const SDL_Scancode& aKey) {}

      virtual void ButtonPressed(const SDL_GameControllerButton& aButton) {}
      virtual void ButtonReleased(const SDL_GameControllerButton& aButton) {} 

    private:
      CallbackHolder mCallbacks;
  };
}
