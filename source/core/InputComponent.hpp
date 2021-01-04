#ifndef INPUTCOMPONENT_HPP
#define INPUTCOMPONENT_HPP

#include "Component.hpp"

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
      virtual void HandleKeyPress(int aKey,
                                  int aScancode,
                                  int aMods) {}
      virtual void HandleKeyRelease(int aKey,
                                    int aScancode,
                                    int aMods) {}

      /**
       * Mouse callbacks.
       */
      virtual void HandleMouseMoved(double aXPosition,
                                    double aYPosition) {}
      virtual void HandleMouseEnteredOrLeft(bool aEntered) {}
      virtual void HandleMouseButtonPress(int aButton,
                                          int aAction,
                                          int aMods) {}
      virtual void HandleMouseScrolled(double aXOffset,
                                       double aYOffset) {}
  };
}

#endif
