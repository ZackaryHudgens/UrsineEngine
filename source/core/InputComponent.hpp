#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include "Component.hpp"
#include "CoreSignals.hpp"

namespace core
{
  /**
   * A base class for all components that respond to input. Connects to each
   * relevant signal on construction and contains virtual functions for
   * supported input methods.
   */
  class InputComponent : public Component
  {
    public:
      InputComponent();

      virtual void Update() override {}

      /**
       * Keyboard callbacks.
       */
      virtual void HandleKeyPress(const KeyCode& aCode,
                                  int aMods) {}
      virtual void HandleKeyRelease(const KeyCode& aCode,
                                    int aMods) {}

      /**
       * Mouse callbacks.
       */
      virtual void HandleMouseMoved(double aXPosition,
                                    double aYPosition) {}
      virtual void HandleMouseEnteredOrLeft(bool aEntered) {}
      virtual void HandleMouseButtonPress(const MouseButton& aButton,
                                          int aMods) {}
      virtual void HandleMouseScrolled(double aXOffset,
                                       double aYOffset) {}
  };
}

#endif
