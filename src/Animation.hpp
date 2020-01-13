#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>
#include <vector>

#include "Texture.hpp"
#include "Vector2D.hpp"

using gMath::Vector2D;

namespace gCore
{
  class Animation
  {
    public:
      Animation();

      void Update();
      void Render(const Vector2D& aPosition, double aScalar = 1.0) const;

      void SetTexture(std::unique_ptr<Texture> aTexture);
      void AddFrame(const SDL_Rect& aFrame);

      void SetSpeed(double aSpeed) { mSpeed = aSpeed; }

      void Reset();

    private:
      std::unique_ptr<Texture> mTexture;
      std::vector<SDL_Rect> mFrames;

      int mCurrentFrame;
      double mSpeed;
      double mFrameTimer;
  };
}

#endif
