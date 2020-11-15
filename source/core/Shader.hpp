#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>

namespace core
{
  /**
   * A class that encapsulates a GLSL shader.
   */
  class Shader
  {
    public:
      Shader(const std::string& aVertexPath,
             const std::string& aFragmentPath);

      void Activate() const;

      void SetBool(const std::string& aName, bool aValue) const;
      void SetInt(const std::string& aName, int aValue) const;
      void SetFloat(const std::string& aName, float aValue) const;
      void SetMat4(const std::string& aName, const glm::mat4& aMat) const;

    private:
      void LoadShaderAsString(std::string& aString,
                              const std::string& aShaderPath);
      void CompileShader(unsigned int& aShaderID,
                         const std::string& aShaderSource,
                         GLenum aShaderType);
      void CreateProgram(unsigned int aVertexID,
                         unsigned int aFragmentID);

      unsigned int mProgramId;
  };
}

#endif
