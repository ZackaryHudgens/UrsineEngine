#include "AnimationManager.hpp"

#include "GameObject.hpp"

using gCore::AnimationManager;

AnimationManager::AnimationManager()
  : GraphicalComponent()
{
}

/**
 * Updates the current Animation.
 */
void AnimationManager::Update()
{
  auto ani = mAnimationMap.find(mCurrentAnimation);
  if(ani != mAnimationMap.end())
  {
    ani->second->Update();
  }
}

/**
 * Renders the current Animation.
 */
void AnimationManager::Render() const
{
  auto ani = mAnimationMap.find(mCurrentAnimation);
  if(ani != mAnimationMap.end())
  {
    ani->second->Render(GetParent()->GetLocation());
  }
}
