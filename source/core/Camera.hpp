#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/fwd.hpp>

#include "GameObject.hpp"

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

      void SetFOV(double aFOV) { mFOV = aFOV; }
      double GetFOV() const    { return mFOV; }

      void SetNearPlane(double aNearPlane) { mNearPlane = aNearPlane; }
      double GetNearPlane() const          { return mNearPlane; }

      void SetFarPlane(double aFarPlane) { mFarPlane = aFarPlane; }
      double GetFarPlane() const         { return mFarPlane; }

      glm::mat4 GetViewMatrix() const;

      void LookAt(const GameObject& aObject);
      void LookAt(const glm::vec3& aPosition);

      void Translate(const glm::vec3& aVector) override;
      void Rotate(double aDegrees, const glm::vec3& aAxis) override;

    private:
      void UpdateVectors();

      double mFOV;
      double mNearPlane;
      double mFarPlane;

      glm::vec3 mTarget;

      glm::vec3 mRightVector;  // x-axis
      glm::vec3 mUpVector;     // y-axis
      glm::vec3 mFrontVector;  // z-axis
  };
}

#endif
