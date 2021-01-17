#include "InputComponent.hpp"

#include "CoreSignals.hpp"

using core::InputComponent;

/**
 * Constructor for the InputComponent class. Connects to each relevant
 * signal in CoreObservers.
 */
InputComponent::InputComponent()
{
  /**
   * Keyboard callbacks.
   */

  // Key Pressed callback
  core::KeyPressed.Connect(*this, [this](const KeyCode& aCode,
                                         int aMods)
  {
    this->HandleKeyPress(aCode, aMods);
  });

  // Key Released callback
  core::KeyReleased.Connect(*this, [this](const KeyCode& aCode,
                                          int aMods)
  {
    this->HandleKeyRelease(aCode, aMods);
  });

  /**
   * Mouse callbacks.
   */

  // Mouse Moved callback
  core::MouseMoved.Connect(*this, [this](double aXPosition,
                                         double aYPosition)
  {
    this->HandleMouseMoved(aXPosition, aYPosition);
  });

  // Mouse Entered or Left callback
  core::MouseEnteredOrLeft.Connect(*this, [this](bool aEntered)
  {
    this->HandleMouseEnteredOrLeft(aEntered);
  });

  // Mouse Button Pressed callback
  core::MouseButtonPressed.Connect(*this, [this](const MouseButton& aButton,
                                                 int aMods)
  {
    this->HandleMouseButtonPress(aButton, aMods);
  });

  // Mouse Scrolled callback
  core::MouseScrolled.Connect(*this, [this](double aXOffset,
                                            double aYOffset)
  {
    this->HandleMouseScrolled(aXOffset, aYOffset);
  });
}
