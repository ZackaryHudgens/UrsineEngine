#include "Camera.hpp"

#include "Environment.hpp"

using gCore::Camera;

Camera::Camera()
  : mCurrentZoom(1.0)
  , mTargetZoom(1.0)
  , mScrollSpeed(1.0)
  , mZoomSpeed(1.0)
{
  int w, h;
  SDL_GetWindowSize(env.GetWindow(), &w, &h);
  mCurrentRect = SDL_Rect{0, 0, w, h};
  mTargetRect = mCurrentRect;
}

Camera::Camera(const SDL_Rect& aRect)
  : mCurrentZoom(1.0)
  , mTargetZoom(1.0)
  , mScrollSpeed(1.0)
  , mZoomSpeed(1.0)
{
  mCurrentRect = aRect;
  mTargetRect = aRect;
}

void Camera::Update()
{
}
