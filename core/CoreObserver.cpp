#include "CoreObserver.hpp"

using core::CoreObserver;

// Static instantiations.

/******************************************************************************
 * Mouse and keyboard input callbacks.
 *****************************************************************************/

CoreObserver::mouseMovedCallback CoreObserver::MouseMoved;
CoreObserver::singleClickCallback CoreObserver::SingleClick;
CoreObserver::doubleClickCallback CoreObserver::DoubleClick;
CoreObserver::mouseReleasedCallback CoreObserver::MouseReleased;
CoreObserver::mouseWheelCallback CoreObserver::MouseScroll;

/******************************************************************************
 * Controller input callbacks.
 *****************************************************************************/


/******************************************************************************
 * Animation callbacks.
 *****************************************************************************/
