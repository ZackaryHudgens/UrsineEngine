#include "CoreObserver.hpp"

using gCore::CoreObserver;

// Static instantiations.

/******************************************************************************
 * Mouse and keyboard input callbacks.
 *****************************************************************************/

CoreObserver::mouseMovedCallback CoreObserver::MouseMoved;
CoreObserver::singleClickCallback CoreObserver::SingleClick;
CoreObserver::doubleClickCallback CoreObserver::DoubleClick;
CoreObserver::mouseReleasedCallback CoreObserver::MouseReleased;
CoreObserver::mouseWheelCallback CoreObserver::MouseScroll;
CoreObserver::keyPressedCallback CoreObserver::KeyPressed;
CoreObserver::keyReleasedCallback CoreObserver::KeyReleased;

/******************************************************************************
 * Controller input callbacks.
 *****************************************************************************/

CoreObserver::buttonPressedCallback CoreObserver::ButtonPressed;
CoreObserver::buttonReleasedCallback CoreObserver::ButtonReleased;

/******************************************************************************
 * Animation callbacks.
 *****************************************************************************/

CoreObserver::animationAdvancedCallback CoreObserver::AnimationAdvanced;
