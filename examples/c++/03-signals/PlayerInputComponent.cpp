#include "PlayerInputComponent.hpp"

#include "PlayerSignals.hpp"

#include <iostream>

// Included here to get the name of the key via glfwGetKeyName().
// TODO: Every InputComponent is going to need this. Find a better way?
#include <GLFW/glfw3.h>

using example_three::PlayerInputComponent;

PlayerInputComponent::PlayerInputComponent()
  : InputComponent()
{
}

void PlayerInputComponent::HandleKeyPress(int aKey,
                                          int aScancode,
                                          int aMods)
{
  const char* keyName = glfwGetKeyName(aKey, aScancode);
  if(keyName != nullptr)
  {
    std::cout << "You just pressed "
              << keyName
              << "!"
              << std::endl;

    /**
     * The key was the Q key, so we notify the QPressed signal, passing this
     * component's parent as the argument. Now, any Observers connected to
     * the QPressed signal are made aware that this player just pressed Q.
     */
    if(aKey == GLFW_KEY_Q)
    {
      //QPressed.Notify(GetParent());
    }
  }
  else
  {
    std::cout << "You just pressed a key GLFW didn't recognize!" << std::endl;
  }
}
