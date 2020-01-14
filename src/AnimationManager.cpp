#include "AnimationManager.hpp"

#include "GameObject.hpp"

using gCore::AnimationManager;

AnimationManager::AnimationManager()
  : GraphicalComponent()
  , mCurrentAnimation(nullptr)
{
}

/**
 * Updates the current Animation.
 */
void AnimationManager::Update()
{
  if(mCurrentAnimation != nullptr)
  {
    mCurrentAnimation->Update();
  }
}

/**
 * Renders the current Animation.
 */
void AnimationManager::Render() const
{
  if(mCurrentAnimation != nullptr)
  {
    mCurrentAnimation->Render(GetParent()->GetLocation());
  }
}

/**
 * Adds an animation to the manager, using a string name
 * as an identifier. If an Animation with that name
 * already exists, this function returns false.
 *
 * @param aName The name of the Animation.
 * @param aAnimation The Animation to add.
 */
bool AnimationManager::AddAnimation(const std::string& aName,
                                    std::unique_ptr<Animation> aAnimation)
{
  auto ani = mAnimationMap.find(aName);
  if(ani == mAnimationMap.end())
  {
    mAnimationMap.emplace(aName, std::move(aAnimation));
    return true;
  }
  else
  {
    return false;
  }
}

/**
 * Resets the current Animation, then changes the current Animation
 * to the one specified by the given identifier.
 *
 * @param aName The name of the desired Animation.
 */
void AnimationManager::SetAnimation(const std::string& aName)
{
  mCurrentAnimation->Reset();

  auto ani = mAnimationMap.find(aName);
  if(ani != mAnimationMap.end())
  {
    mCurrentAnimation = ani->second.get();
  }
  else
  {
    mCurrentAnimation = nullptr;
  }
}
