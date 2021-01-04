#include "PlayerObject.hpp"

#include "PlayerInputComponent.hpp"

using example_two::PlayerObject;
using example_two::PlayerInputComponent;

PlayerObject::PlayerObject()
  : core::GameObject()
{
  AddComponent(std::make_unique<PlayerInputComponent>());
}
