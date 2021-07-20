#include "SpriteComponent.hpp"

#include "Environment.hpp"

#include <algorithm>
#include <iostream>

using UrsineRenderer::SpriteComponent;
using UrsineRenderer::TextureClip;

SpriteComponent::SpriteComponent()
  : GraphicalComponent()
  , mCurrentAnimation(nullptr)
{
}

void SpriteComponent::Update()
{
  if(mCurrentAnimation != nullptr)
  {
    mCurrentAnimation->Update(env.GetTime());
  }
}

void SpriteComponent::Render() const
{
  mMesh.Render();
}

void SpriteComponent::SetTexture(const Texture& aTexture)
{
  // Remove any old textures.
  mMesh.GetTextures().clear();

  // Add the new texture.
  mMesh.AddTexture(aTexture);

  // By default, render the entire texture.
  unsigned int w = aTexture.GetData().mWidth;
  unsigned int h = aTexture.GetData().mHeight;
  TextureClip clip{0, 0, w, h};
  SetRenderDimensions(clip);
}

void SpriteComponent::SetRenderDimensions(const TextureClip& aClip)
{
  // First, normalize the width and height.
  double magnitude = std::pow(aClip.mWidth, 2) + std::pow(aClip.mHeight, 2);
  magnitude = std::sqrt(magnitude);

  double normalizedWidth = aClip.mWidth / magnitude;
  double normalizedHeight = aClip.mHeight / magnitude;

  // Next, use the normalized width and height to create a rectangle.
  mMesh.GetVertices().clear();
  MeshVertex vertex;
  vertex.mPosition = glm::vec3(0.0, 0.0, 0.0);  // bottom left
  vertex.mTexCoords = glm::vec2(aClip.mX, aClip.mY);
  mMesh.AddVertex(vertex);
  vertex.mPosition = glm::vec3(normalizedWidth, 0.0, 0.0);  // bottom right
  vertex.mTexCoords = glm::vec2(aClip.mX + aClip.mWidth, aClip.mY);
  mMesh.AddVertex(vertex);
  vertex.mPosition = glm::vec3(normalizedWidth, normalizedHeight, 0.0);  // top right
  vertex.mTexCoords = glm::vec2(aClip.mX + aClip.mWidth, aClip.mY + aClip.mHeight);
  mMesh.AddVertex(vertex);
  vertex.mPosition = glm::vec3(0.0, normalizedHeight, 0.0);  // bottom right
  vertex.mTexCoords = glm::vec2(aClip.mX, aClip.mY + aClip.mHeight);
  mMesh.AddVertex(vertex);
}

bool SpriteComponent::CreateAnimation(const std::string& aName)
{
  bool success = true;

  auto findAnimation = [&](const SpriteAnimation& aAnimation)
  {
    return aAnimation.GetName() == aName;
  };

  auto foundAnimation = std::find_if(mAnimations.begin(), mAnimations.end(), findAnimation);
  if(foundAnimation == mAnimations.end())
  {
    mAnimations.emplace_back(SpriteAnimation(aName, *this));
  }
  else
  {
    success = false;
  }

  return success;
}

bool SpriteComponent::SetAnimation(const std::string& aName)
{
  bool success = true;

  auto findAnimation = [&](const SpriteAnimation& aAnimation)
  {
    return aAnimation.GetName() == aName;
  };

  auto foundAnimation = std::find_if(mAnimations.begin(), mAnimations.end(), findAnimation);
  if(foundAnimation != mAnimations.end())
  {
    mCurrentAnimation = &(*foundAnimation);
  }
  else
  {
    success = false;
  }

  return success;
}

std::string SpriteComponent::GetCurrentAnimationName() const
{
  std::string name;

  if(mCurrentAnimation != nullptr)
  {
    name = mCurrentAnimation->GetName();
  }

  return name;
}

void SpriteComponent::AddFrameToAnimation(const TextureClip& aClip)
{
  if(mCurrentAnimation != nullptr)
  {
    mCurrentAnimation->AddFrame(aClip);
  }
  else
  {
    std::cout << "No animation has been set!" << std::endl;
  }
}

void SpriteComponent::SetFrameOfAnimation(int aFrameIndex)
{
  if(mCurrentAnimation != nullptr)
  {
    mCurrentAnimation->SetCurrentFrame(aFrameIndex);

    // Update the render dimensions.
    if(mCurrentAnimation->GetCurrentFrameData() != nullptr)
    {
      SetRenderDimensions(*mCurrentAnimation->GetCurrentFrameData());
    }
  }
  else
  {
    std::cout << "No animation has been set!" << std::endl;
  }
}

void SpriteComponent::SetSpeedOfAnimation(double aSpeed)
{
  if(mCurrentAnimation != nullptr)
  {
    mCurrentAnimation->SetSpeed(aSpeed);
  }
  else
  {
    std::cout << "No animation has been set!" << std::endl;
  }
}

SpriteComponent::SpriteAnimation::SpriteAnimation(const std::string& aName,
                                                  SpriteComponent& aParent)
  : mName(aName)
  , mParent(&aParent)
  , mSpeed(1.0)
  , mPreviousTime(0.0)
  , mCurrentFrame(0)
{
}

void SpriteComponent::SpriteAnimation::Update(double aTime)
{
  // First, determine the elapsed time since the last update.
  double elapsedTime = aTime - mPreviousTime;
  mPreviousTime = aTime;

  // Next, if the elapsedTime is greater than the animation speed,
  // move to the next frame of the animation.
  if(elapsedTime > mSpeed)
  {
    ++mCurrentFrame;

    // If the current frame index is beyond the number of available frames,
    // loop back to the beginning of the animation.
    if(mCurrentFrame > (mFrames.size() - 1))
    {
      mCurrentFrame = 0;
      SpriteAnimationComplete.Notify(mName, *mParent);
    }

    // Finally, update the SpriteComponent's render dimensions.
    mParent->SetRenderDimensions(mFrames.at(mCurrentFrame));
    SpriteAnimationFrameChanged.Notify(mName, mCurrentFrame, *mParent);
  }
}

void SpriteComponent::SpriteAnimation::AddFrame(const TextureClip& aClip)
{
  mFrames.emplace_back(aClip);
}

TextureClip* SpriteComponent::SpriteAnimation::GetCurrentFrameData()
{
  TextureClip* data = nullptr;

  if(!mFrames.empty())
  {
    data = &mFrames.at(mCurrentFrame);
  }

  return data;
}

/*****************************************************************************/
void SpriteComponent::HandleShaderAdded(GraphicalComponent* aComponent,
                                        const Shader& aShader,
                                        const std::string& aName)
{
  if(aComponent == this)
  {
    mMesh.AddShader(aName, aShader);
  }
}

/*****************************************************************************/
void SpriteComponent::HandleShaderRemoved(GraphicalComponent* aComponent,
                                          const std::string& aName)
{
  if(aComponent == this)
  {
    mMesh.RemoveShader(aName);
  }
}

/*****************************************************************************/
void SpriteComponent::HandleShaderChanged(GraphicalComponent* aComponent,
                                          const std::string& aName)
{
  if(aComponent == this)
  {
    mMesh.SetCurrentShader(aName);
  }
}

/**
 * Animation signals.
 */
UrsineRenderer::SpriteAnimationFrameChangedSignal UrsineRenderer::SpriteAnimationFrameChanged;
UrsineRenderer::SpriteAnimationCompleteSignal     UrsineRenderer::SpriteAnimationComplete;
