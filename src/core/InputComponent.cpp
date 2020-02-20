#include "InputComponent.hpp"

using gCore::InputComponent;

InputComponent::InputComponent()
{
  mCallbacks.Add(CoreObserver::MouseMoved.Connect(
    [&](int aX, int aY) { MouseMoved(aX, aY); }));

  mCallbacks.Add(CoreObserver::SingleClick.Connect(
    [&](int aX, int aY) { SingleClick(aX, aY); }));

  mCallbacks.Add(CoreObserver::DoubleClick.Connect(
    [&](int aX, int aY) { DoubleClick(aX, aY); }));

  mCallbacks.Add(CoreObserver::MouseReleased.Connect(
    [&](int aX, int aY) { MouseReleased(aX, aY); }));

  mCallbacks.Add(CoreObserver::MouseScroll.Connect(
    [&](int aHorz, int aVert) { MouseScroll(aHorz, aVert); }));

  mCallbacks.Add(CoreObserver::KeyPressed.Connect(
    [&](const SDL_Scancode& aKey) { KeyPressed(aKey); }));

  mCallbacks.Add(CoreObserver::KeyReleased.Connect(
    [&](const SDL_Scancode& aKey) { KeyReleased(aKey); }));

  mCallbacks.Add(CoreObserver::ButtonPressed.Connect(
    [&](const SDL_GameControllerButton& aButton) { ButtonPressed(aButton); }));

  mCallbacks.Add(CoreObserver::ButtonReleased.Connect(
    [&](const SDL_GameControllerButton& aButton) { ButtonReleased(aButton); }));
}
