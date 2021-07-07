#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"

using UrsineCore::GameObject;

namespace UrsineRenderer
{
  /**
   * The Camera object is used to view a Scene; the view matrix
   * returned by GetViewMatrix() is passed by default into all
   * shaders with a mat4 uniform named "viewMatrix".
   */
  class Camera : public GameObject
  {
    public:

      /**
       * Constructor. By default, this object's name is "Camera".
       *
       * @param aName The name of this GameObject.
       */
      Camera(const std::string& aName = "Camera");

      /**
       * Returns a view matrix calculated using this Camera's position,
       * its forward vector, and its up vector. This matrix is passed to
       * every shader by default.
       *
       * @return A view matrix calculated based on this Camera's coordinates
       *         and which direction it is looking.
       */
      glm::mat4 GetViewMatrix() const;

      /**
       * Turns the camera to look at a GameObject.
       *
       * @param aObject The GameObject to look at.
       */
      void LookAt(const GameObject& aObject);

      /**
       * Turns the camera to look at a specific position in 3D space.
       *
       * @param aPos The position to look at.
       */
      void LookAt(const glm::vec3 aPos);

    private:
      glm::vec3 mForwardVector;
      glm::vec3 mUpVector;
      glm::vec3 mRightVector;
  };
}

#endif
