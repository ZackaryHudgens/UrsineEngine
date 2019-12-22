#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SDL2/SDL.h>

class Camera
{
  public:
    Camera();
    Camera(const SDL_Rect& aRect);

    void Update();

    void SetRect(const SDL_Rect& aRect) { mTargetRect = aRect; }
    const SDL_Rect& GetRect() const     { return mCurrentRect; }

    void SetZoom(double aZoom) { mTargetZoom = aZoom; }
    double GetZoom() const     { return mCurrentZoom; }

    void SetScrollSpeed(double aSpeed) { mScrollSpeed = aSpeed; }
    void SetZoomSpeed(double aSpeed)   { mZoomSpeed = aSpeed; }

  private:
    SDL_Rect mCurrentRect;
    SDL_Rect mTargetRect;

    double mCurrentZoom;
    double mTargetZoom;

    double mScrollSpeed;
    double mZoomSpeed;
};

#endif
