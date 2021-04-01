#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "GameObject.hpp"

using UrsineCore::GameObject;

namespace UrsineRenderer
{
  class Camera : public GameObject
  {
    public:
      Camera();

      glm::mat4 GetViewMatrix() const;

      void LookAt(const GameObject& aObject);
      void LookAt(const glm::vec3 aPos);

    private:
      glm::vec3 mForwardVector;
      glm::vec3 mUpVector;
      glm::vec3 mRightVector;
  };
}

#endif
