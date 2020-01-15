#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <map>

#include "Animation.hpp"
#include "GraphicalComponent.hpp"

namespace gCore
{
  /**
   * A container Component for Animations. Note that this class
   * has an empty implementation of ProcessEvent().
   */
  class AnimationManager : public GraphicalComponent
  {
    public:
      AnimationManager();

      void Update() override;
      void Render() const override;
      void ProcessEvent(const SDL_Event& aEvent) override {}

      bool AddAnimation(const std::string& aName,
                        std::unique_ptr<Animation> aAnimation);
      void SetAnimation(const std::string& aName);

    private:
      std::map<std::string, std::unique_ptr<Animation>> mAnimationMap;
      Animation* mCurrentAnimation;
  };
}

#endif
