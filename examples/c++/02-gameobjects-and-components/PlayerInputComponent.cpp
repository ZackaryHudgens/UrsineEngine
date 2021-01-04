#include "PlayerInputComponent.hpp"

#include <iostream>

// Included here to get the name of the key via glfwGetKeyName().
// TODO: Every InputComponent is going to need this. Find a better way?
#include <GLFW/glfw3.h>

using example_two::PlayerInputComponent;

PlayerInputComponent::PlayerInputComponent()
  : InputComponent()
{
}

void PlayerInputComponent::HandleKeyPress(int aKey,
                                          int aScancode,
                                          int aMods)
{
  std::cout << "You just pressed "
            << glfwGetKeyName(aKey, aScancode)
            << "!"
            << std::endl;
}
