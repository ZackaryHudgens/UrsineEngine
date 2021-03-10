#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace UrsineRenderer
{
  /**
   * A class that encapsulates a GLSL shader.
   */
  class Shader
  {
    public:
      Shader(const char* aVertexSource,
             const char* aFragmentSource);

      const std::string& GetVertexSource() const   { return mVertexSource; }
      const std::string& GetFragmentSource() const { return mFragmentSource; }

      void Activate() const;

      void SetBool(const std::string& aName, bool aValue) const;
      void SetInt(const std::string& aName, int aValue) const;
      void SetFloat(const std::string& aName, float aValue) const;
      void SetVec3(const std::string& aName, const glm::vec3& aVec) const;
      void SetMat4(const std::string& aName, const glm::mat4& aMat) const;

    private:
      void CompileShader(unsigned int& aShaderID,
                         const std::string& aShaderSource,
                         GLenum aShaderType);
      void CreateProgram(unsigned int aVertexID,
                         unsigned int aFragmentID);

      std::string mVertexSource;
      std::string mFragmentSource;

      unsigned int mProgramId;
  };
}

#endif
