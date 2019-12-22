#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <vector>
#include <memory>

#include "Texture.hpp"

class Animation
{
  public:
    Animation();

    void Update();
    void Render(const Vector2D& aPosition, double aScalar = 1.0) const;

    void SetTexture(std::unique_ptr<Texture> aTexture);
    void AddFrame(const SDL_Rect& aFrame);

    void SetSpeed(double aSpeed) { mSpeed = aSpeed; }

  private:
    std::unique_ptr<Texture> mTexture;
    std::vector<SDL_Rect> mFrames;

    int mCurrentFrame;
    double mSpeed;
    double mFrameTimer;
};

#endif
