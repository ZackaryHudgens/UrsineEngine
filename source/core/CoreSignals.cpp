#include "CoreSignals.hpp"

#include <GLFW/glfw3.h>

/**
 * Returns the name of a key as a string.
 *
 * @param aCode The KeyCode whose name to look up.
 */
std::string core::GetKeyName(const core::KeyCode& aCode)
{
  int codeAsInt = (int)aCode;
  std::string name = glfwGetKeyName(codeAsInt, glfwGetKeyScancode(codeAsInt));

  return name;
}

/**
 * Returns true if the given KeyboardModifier is active in the given
 * mods.
 *
 * @param aMod The modifier for which to determine to determine
 * active/inactive status.
 * @param aMods The list of modifiers to check.
 */
bool core::IsModifierActive(const KeyboardModifier& aMod, int aMods)
{
  int modAsInt = (int)aMod;
  return (aMods & (1 << modAsInt));
}

/**
 * Input signals.
 */
core::KeyPressedSignal         core::KeyPressed;
core::KeyReleasedSignal        core::KeyReleased;
core::MouseMovedSignal         core::MouseMoved;
core::MouseEnteredOrLeftSignal core::MouseEnteredOrLeft;
core::MouseButtonPressedSignal core::MouseButtonPressed;
core::MouseScrolledSignal      core::MouseScrolled;
