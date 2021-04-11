#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "GraphicalComponent.hpp"
#include "MeshComponent.hpp"
#include "Signal.hpp"

namespace UrsineRenderer
{
  struct TextureClip
  {
    unsigned int mX;
    unsigned int mY;
    unsigned int mWidth;
    unsigned int mHeight;
  };

  class SpriteComponent : public GraphicalComponent
  {
    public:
      SpriteComponent();

      void Update() override;
      void Render() const override;

      void SetTexture(const Texture& aTexture);
      void SetRenderDimensions(const TextureClip& aClip);

      MeshComponent& GetMesh() { return mMesh; }

      void CreateAnimation(const std::string& aName);
      void SetAnimation(const std::string& aName);
      std::string GetCurrentAnimationName() const;
      void AddFrameToAnimation(const TextureClip& aClip);
      void SetFrameOfAnimation(int aFrameIndex);
      void SetSpeedOfAnimation(double aSpeed);

    private:
      class SpriteAnimation
      {
        public:
          SpriteAnimation(const std::string& aName,
                          SpriteComponent& aParent);

          void Update(double aTime);

          std::string GetName() const { return mName; }

          void AddFrame(const TextureClip& aClip);

          void SetCurrentFrame(int aFrameIndex) { mCurrentFrame = aFrameIndex; }
          int GetCurrentFrameIndex() const      { return mCurrentFrame; }

          TextureClip* GetCurrentFrameData();

          void SetSpeed(double aSpeed) { mSpeed = aSpeed; }

        private:
          typedef std::vector<TextureClip> FrameList;
          FrameList mFrames;

          std::string      mName;
          SpriteComponent* mParent;

          double mSpeed;
          double mPreviousTime;

          int mCurrentFrame;
      };

      MeshComponent mMesh;

      typedef std::vector<SpriteAnimation> AnimationList;
      AnimationList mAnimations;
      SpriteAnimation* mCurrentAnimation;
  };

  /**
   * SpriteComponent signals.
   */
  typedef UrsineCore::SignalT<std::string, int, SpriteComponent&> SpriteAnimationFrameChangedSignal;
  typedef UrsineCore::SignalT<std::string, SpriteComponent&> SpriteAnimationCompleteSignal;

  extern SpriteAnimationFrameChangedSignal SpriteAnimationFrameChanged;
  extern SpriteAnimationCompleteSignal     SpriteAnimationComplete;
}

#endif
