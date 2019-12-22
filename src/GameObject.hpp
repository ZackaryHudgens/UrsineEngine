#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <map>
#include <memory>
#include <string>

#include "Animation.hpp"
#include "Camera.hpp"
#include "Texture.hpp"
#include "Vector2D.hpp"

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

    void AddAnimation(const std::string& aName,
                      std::unique_ptr<Animation> aAnimation);
    void SetAnimation(const std::string& aName);

  private:
    std::string mCurrentAnimation;
    std::map<std::string, std::unique_ptr<Animation>> mAnimations;

    Vector2D mLocation;
    Vector2D mVelocity;
};

#endif
