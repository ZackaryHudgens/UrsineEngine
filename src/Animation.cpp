#include "Animation.hpp"

#include "Environment.hpp"

using gCore::Animation;
using gCore::CoreObserver;

Animation::Animation()
  : mCurrentFrame(0)
  , mSpeed(0)
  , mFrameTimer(0)
{
}

/**
 * Updates the Animation by calculating the elapsed time since the last update
 * and determine if the animation should advance to the next frame.
 */
void Animation::Update()
{
  double elapsedTime = env.GetTime() - mFrameTimer;
  if(elapsedTime > mSpeed)
  {
    ++mCurrentFrame;

    CoreObserver::AnimationAdvanced.Notify(*this);

    if(mCurrentFrame > mFrames.size() - 1)  // Loop back around.
    {
      mCurrentFrame = 0;
    }
    mFrameTimer = env.GetTime();
  }
}

/**
 * Renders the Animation at the given world position.
 * TODO: how to handle screen space vs. world rendering?
 *
 * @param aPosition The world position to render this Animation.
 */
void Animation::Render(const Vector2D& aPosition) const
{
  if(mCurrentFrame < mFrames.size())
  {
    mTexture->RenderPortion(aPosition, mFrames.at(mCurrentFrame));
  }
}

/**
 * Sets the current texture (spritesheet).
 *
 * @param aTexture The Texture to take ownership of.
 */
void Animation::SetTexture(std::unique_ptr<Texture> aTexture)
{
  mTexture = std::move(aTexture);
}

/**
 * Adds a frame to the Animation.
 *
 * @param aFrame A clipping rectangle.
 */
void Animation::AddFrame(const SDL_Rect& aFrame)
{
  mFrames.emplace_back(aFrame);
}

/**
 * Resets the Animation to the first frame and resets the timer.
 */
void Animation::Reset()
{
  mCurrentFrame = 0;
  mFrameTimer = 0;
}
