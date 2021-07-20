#ifndef SPRITECOMPONENT_HPP
#define SPRITECOMPONENT_HPP

#include "GraphicalComponent.hpp"
#include "MeshComponent.hpp"
#include "Signal.hpp"

namespace UrsineRenderer
{
  /**
   * A struct that contains all the information needed to render a
   * rectangular portion of a texture.
   */
  struct TextureClip
  {
    unsigned int mX;       // The left side of the rectangle in pixels.
    unsigned int mY;       // The bottom of the rectangle in pixels.
    unsigned int mWidth;   // The width of the rectangle in pixels.
    unsigned int mHeight;  // The height of the rectangle in pixels.
  };

  /**
   * A GraphicalComponent that can be used to represent a 2D sprite.
   * Internally, this class contains a MeshComponent used to render
   * the image as a 2D rectangle. It also contains a simple 2D animation
   * system, which can be used to render portions of a larger texture
   * (typically a spritesheet).
   */
  class SpriteComponent : public GraphicalComponent
  {
    public:

      /**
       * Constructor.
       */
      SpriteComponent();

      /**
       * Updates the current animation and advances frames if necessary.
       */
      void Update() override;

      /**
       * Renders the sprite as a 2D rectangular mesh.
       */
      void Render() const override;

      /**
       * Sets the texture to use with this sprite (typically a spritesheet).
       *
       * @param aTexture The texture to use.
       */
      void SetTexture(const Texture& aTexture);

      /**
       * Sets the SpriteComponent to render only a rectangular portion of
       * the set texture. Note that any animations may override this.
       *
       * @param aClip The dimensions of the rectangle.
       */
      void SetRenderDimensions(const TextureClip& aClip);

      /**
       * Creates a new animation with the given name. This fails if an
       * animation with the given name already exists.
       *
       * @param aName The name of the animation.
       * @return True if successful, false otherwise.
       */
      bool CreateAnimation(const std::string& aName);

      /**
       * Sets the current animation. This fails if no animation with the
       * given name exists.
       *
       * @param aName The name of the animation.
       * @return True if successful, false otherwise.
       */
      bool SetAnimation(const std::string& aName);

      /**
       * Returns the name of the current animation.
       *
       * @return The name of the current animation.
       */
      std::string GetCurrentAnimationName() const;

      /**
       * Adds a rectangular frame to the current animation.
       *
       * @param aClip The dimensions of the rectangle.
       */
      void AddFrameToAnimation(const TextureClip& aClip);

      /**
       * Sets the frame of the current animation. The frames advance
       * normally depending on animation speed, but this function can be
       * used to force the animation into a specific frame.
       *
       * @param aFrameIndex The index of the desired frame, beginning at 0.
       */
      void SetFrameOfAnimation(int aFrameIndex);

      /**
       * Set the speed of the current animation in seconds (the number of
       * seconds to wait before advancing to the next frame).
       *
       * @param aSpeed The speed of the animation in seconds.
       */
      void SetSpeedOfAnimation(double aSpeed);

    private:

      /**
       * A nested class that encapsulates a 2D animation.
       */
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

      /**
       */
      void HandleShaderAdded(GraphicalComponent* aComponent,
                             const Shader& aShader,\
                             const std::string& aName);

      /**
       */
      void HandleShaderRemoved(GraphicalComponent* aComponent,
                               const std::string& aName);

      /**
       */
      void HandleShaderChanged(GraphicalComponent* aComponent,
                               const std::string& aName);

      typedef std::vector<SpriteAnimation> AnimationList;

      MeshComponent mMesh;

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
