#include "PlayerObject.hpp"

#include "PlayerInputComponent.hpp"

using example_three::PlayerObject;
using example_three::PlayerInputComponent;

PlayerObject::PlayerObject(const std::string& aName)
  : core::GameObject()
  , mName(aName)
{
  AddComponent(std::make_unique<PlayerInputComponent>());
}
