#include "CoreSignals.hpp"

#include <GLFW/glfw3.h>

/**
 * Returns the name of a key as a string.
 *
 * @param aCode The KeyCode whose name to look up.
 */
std::string core::GetKeyName(const core::KeyCode& aCode)
{
  std::string name;

  /**
   * Not all keys are supported by glfwGetKeyName; we provide
   * names for them here.
   */
  switch(aCode)
  {
    case KeyCode::eKEY_SPACE:
    {
      name = "space";
      break;
    }
    case KeyCode::eKEY_GRAVE_ACCENT:
    {
      name = "`";
      break;
    }
    case KeyCode::eKEY_ESCAPE:
    {
      name = "escape";
      break;
    }
    case KeyCode::eKEY_ENTER:
    {
      name = "enter";
      break;
    }
    case KeyCode::eKEY_TAB:
    {
      name = "tab";
      break;
    }
    case KeyCode::eKEY_BACKSPACE:
    {
      name = "backspace";
      break;
    }
    case KeyCode::eKEY_INSERT:
    {
      name = "insert";
      break;
    }
    case KeyCode::eKEY_DELETE:
    {
      name = "delete";
      break;
    }
    case KeyCode::eKEY_RIGHT:
    {
      name = "right";
      break;
    }
    case KeyCode::eKEY_LEFT:
    {
      name = "left";
      break;
    }
    case KeyCode::eKEY_DOWN:
    {
      name = "down";
      break;
    }
    case KeyCode::eKEY_UP:
    {
      name = "up";
      break;
    }
    case KeyCode::eKEY_PAGE_UP:
    {
      name = "page up";
      break;
    }
    case KeyCode::eKEY_PAGE_DOWN:
    {
      name = "page down";
      break;
    }
    case KeyCode::eKEY_HOME:
    {
      name = "home";
      break;
    }
    case KeyCode::eKEY_END:
    {
      name = "end";
      break;
    }
    case KeyCode::eKEY_CAPS_LOCK:
    {
      name = "caps lock";
      break;
    }
    case KeyCode::eKEY_SCROLL_LOCK:
    {
      name = "scroll lock";
      break;
    }
    case KeyCode::eKEY_NUM_LOCK:
    {
      name = "num lock";
      break;
    }
    case KeyCode::eKEY_PRINT_SCREEN:
    {
      name = "print screen";
      break;
    }
    case KeyCode::eKEY_PAUSE:
    {
      name = "pause";
      break;
    }
    case KeyCode::eKEY_F1:
    {
      name = "f1";
      break;
    }
    case KeyCode::eKEY_F2:
    {
      name = "f2";
      break;
    }
    case KeyCode::eKEY_F3:
    {
      name = "f3";
      break;
    }
    case KeyCode::eKEY_F4:
    {
      name = "f4";
      break;
    }
    case KeyCode::eKEY_F5:
    {
      name = "f5";
      break;
    }
    case KeyCode::eKEY_F6:
    {
      name = "f6";
      break;
    }
    case KeyCode::eKEY_F7:
    {
      name = "f7";
      break;
    }
    case KeyCode::eKEY_F8:
    {
      name = "f8";
      break;
    }
    case KeyCode::eKEY_F9:
    {
      name = "f9";
      break;
    }
    case KeyCode::eKEY_F10:
    {
      name = "f10";
      break;
    }
    case KeyCode::eKEY_F11:
    {
      name = "f11";
      break;
    }
    case KeyCode::eKEY_F12:
    {
      name = "f12";
      break;
    }
    case KeyCode::eKEY_F13:
    {
      name = "f13";
      break;
    }
    case KeyCode::eKEY_F14:
    {
      name = "f14";
      break;
    }
    case KeyCode::eKEY_F15:
    {
      name = "f15";
      break;
    }
    case KeyCode::eKEY_F16:
    {
      name = "f16";
      break;
    }
    case KeyCode::eKEY_F17:
    {
      name = "f17";
      break;
    }
    case KeyCode::eKEY_F18:
    {
      name = "f18";
      break;
    }
    case KeyCode::eKEY_F19:
    {
      name = "f19";
      break;
    }
    case KeyCode::eKEY_F20:
    {
      name = "f20";
      break;
    }
    case KeyCode::eKEY_F21:
    {
      name = "f21";
      break;
    }
    case KeyCode::eKEY_F22:
    {
      name = "f22";
      break;
    }
    case KeyCode::eKEY_F23:
    {
      name = "f23";
      break;
    }
    case KeyCode::eKEY_F24:
    {
      name = "f24";
      break;
    }
    case KeyCode::eKEY_F25:
    {
      name = "f25";
      break;
    }
    case KeyCode::eKEY_KP_ENTER:
    {
      name = "keypad enter";
      break;
    }
    case KeyCode::eKEY_LEFT_SHIFT:
    {
      name = "left shift";
      break;
    }
    case KeyCode::eKEY_LEFT_CONTROL:
    {
      name = "left control";
      break;
    }
    case KeyCode::eKEY_LEFT_ALT:
    {
      name = "left alt";
      break;
    }
    case KeyCode::eKEY_LEFT_SUPER:
    {
      name = "left super";
      break;
    }
    case KeyCode::eKEY_RIGHT_SHIFT:
    {
      name = "right shift";
      break;
    }
    case KeyCode::eKEY_RIGHT_CONTROL:
    {
      name = "right control";
      break;
    }
    case KeyCode::eKEY_RIGHT_ALT:
    {
      name = "right alt";
      break;
    }
    case KeyCode::eKEY_RIGHT_SUPER:
    {
      name = "right super";
      break;
    }
    case KeyCode::eKEY_MENU:
    {
      name = "menu";
      break;
    }
    default:
    {
      int codeAsInt = (int)aCode;
      auto tempName = glfwGetKeyName(codeAsInt, glfwGetKeyScancode(codeAsInt));
      if(tempName != nullptr)
      {
        name = tempName;
      }
    }
  }

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
core::KeyPressedSignal          core::KeyPressed;
core::KeyReleasedSignal         core::KeyReleased;
core::KeyRepeatedSignal         core::KeyRepeated;
core::MouseMovedSignal          core::MouseMoved;
core::MouseEnteredOrLeftSignal  core::MouseEnteredOrLeft;
core::MouseButtonPressedSignal  core::MouseButtonPressed;
core::MouseButtonReleasedSignal core::MouseButtonReleased;
core::MouseScrolledSignal       core::MouseScrolled;
