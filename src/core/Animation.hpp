#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include <memory>
#include <vector>

#include "Texture.hpp"
#include "Vector2D.hpp"

using gMath::Vector2D;

namespace gCore
{
  /**
   * A class for 2D animation using spirtesheets. To use, create a Texture
   * and load the spritesheet into it. Then, add clipping rectangles
   * using AddFrame().
   */
  class Animation
  {
    public:
      Animation();

      void Update();
      void Render(const Vector2D& aPosition) const;

      void SetTexture(std::unique_ptr<Texture> aTexture);
      void AddFrame(const SDL_Rect& aFrame);

      void SetSpeed(double aSpeed) { mSpeed = aSpeed; }
      int GetFrame() const { return mCurrentFrame; }

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
