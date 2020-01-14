#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <map>

#include "Animation.hpp"
#include "GraphicalComponent.hpp"

namespace gCore
{
  /**
   * A container Component for Animations. Note that this class
   * does not reimplement ProcessEvent() from Component;
   * in order to use this class, a derived class should be created
   * and associated with a spcific type of GameObject,
   * changing animations based on events.
   */
  class AnimationManager : public GraphicalComponent
  {
    public:
      AnimationManager();

      void Update() override;
      void Render() const override;

      bool AddAnimation(const std::string& aName,
                        std::unique_ptr<Animation> aAnimation);
      void SetAnimation(const std::string& aName);

    private:
      std::map<std::string, std::unique_ptr<Animation>> mAnimationMap;
      Animation* mCurrentAnimation;
  };
}

#endif
