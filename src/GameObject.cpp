#include "GameObject.hpp"
#include "Environment.hpp"

#include <algorithm>
#include <iostream>

using gCore::GameObject;

GameObject::GameObject()
  : mLocation(Vector2D(0, 0))
  , mVelocity(Vector2D(0, 0))
{
}

void GameObject::Update()
{
  mLocation += mVelocity;

  if(!mCurrentAnimation.empty())
  {
    mAnimations.find(mCurrentAnimation)->second->Update();
  }
}

void GameObject::Render(const Camera& aCamera) const
{
  if(!mCurrentAnimation.empty())
  {
    mAnimations.find(mCurrentAnimation)->second->Render(mLocation, aCamera.GetZoom());
  }
}

void GameObject::AddAnimation(const std::string& aName,
                              std::unique_ptr<Animation> aAnimation)
{
  if(mAnimations.find(aName) == mAnimations.end())
  {
    mAnimations.emplace(aName, std::move(aAnimation));
  }
}

void GameObject::SetAnimation(const std::string& aName)
{
  if(mAnimations.find(aName) != mAnimations.end())
  {
    mCurrentAnimation = aName;
  }
  else
  {
    mCurrentAnimation = "";
  }
}
