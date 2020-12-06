#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"
#include <glm/fwd.hpp>

namespace core
{
  /*
   * Provides a simulated camera for OpenGL. Note that this isn't
   * a real "camera," but rather just a coordinate system with the
   * camera's position at the origin.
   *
   * Unless the view matrix provided by GetViewMatrix() is applied
   * to a shader uniform, this class doesn't do much of anything.
   */
  class Camera : public GameObject
  {
    public:
      Camera();

      glm::mat4 GetViewMatrix() const;

      void LookAt(const GameObject& aObject);
      void LookAt(const glm::vec4& aLocation);

    private:
      void UpdateVectors();

      glm::vec3 mTarget;

      glm::vec3 mRightVector;  // x-axis
      glm::vec3 mUpVector;     // y-axis
      glm::vec3 mFrontVector;  // z-axis
  };
}

#endif
