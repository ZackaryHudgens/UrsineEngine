#include "InputComponent.hpp"

#include "CoreObservers.hpp"

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
  core::KeyPressed.Connect(*this, [this](int aKey,
                                         int aScancode,
                                         int aAction,
                                         int aMods)
  {
    this->HandleKeyPress(aKey, aScancode, aAction, aMods);
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
  core::MouseButtonPressed.Connect(*this, [this](int aButton,
                                                 int aAction,
                                                 int aMods)
  {
    this->HandleMouseButtonPress(aButton, aAction, aMods);
  });

  // Mouse Scrolled callback
  core::MouseScrolled.Connect(*this, [this](double aXOffset,
                                            double aYOffset)
  {
    this->HandleMouseScrolled(aXOffset, aYOffset);
  });
}
