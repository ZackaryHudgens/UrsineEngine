#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "Camera.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"

using gMath::Vector2D;

namespace gCore
{
  // A game object is the basis for anything that shows up on screen
  // (although it doesn't have to actually show up).
  class GameObject
  {
    public:
      GameObject();

      virtual void Update();
      virtual void Render(const Camera& aCamera) const;

      virtual void ProcessSDLEvent(const SDL_Event& aEvent) {}

      void SetLocation(const Vector2D& aLocation) { mLocation = aLocation; }
      Vector2D GetLocation() const                { return mLocation; }
      void SetVelocity(const Vector2D& aVelocity) { mVelocity = aVelocity; }
      Vector2D GetVelocity() const                { return mVelocity; }

    private:
      std::vector<std::unique_ptr<GameObject>> mChildren;

      Vector2D mLocation;
      Vector2D mVelocity;
  };
}

#endif
