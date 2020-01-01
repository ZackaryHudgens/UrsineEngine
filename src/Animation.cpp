#include "Animation.hpp"

#include <iostream>
#include "Environment.hpp"

using gCore::Animation;

Animation::Animation()
  : mCurrentFrame(1)
  , mSpeed(0)
  , mFrameTimer(0)
{
}

void Animation::Update()
{
  double elapsedTime = env.GetTime() - mFrameTimer;
  if(elapsedTime > mSpeed)
  {
    ++mCurrentFrame;
    if(mCurrentFrame > mFrames.size())
    {
      mCurrentFrame = 1;
    }
    mFrameTimer = env.GetTime();
  }
}

void Animation::Render(const Vector2D& aPosition, double aScalar) const
{
  int frameCount = 0;
  for(const auto& frame : mFrames)
  {
    ++frameCount;
    if(frameCount == mCurrentFrame)
    {
      mTexture->RenderPortion(aPosition, frame, aScalar);
    }
  }
}

void Animation::SetTexture(std::unique_ptr<Texture> aTexture)
{
  mTexture = std::move(aTexture);
}

void Animation::AddFrame(const SDL_Rect& aFrame)
{
  mFrames.emplace_back(aFrame);
}
