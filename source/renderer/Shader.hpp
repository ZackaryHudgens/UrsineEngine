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

      /**
       * Constructor.
       *
       * @param aVertexSource A pointer to the first character of the
       *                      vertex shader.
       * @param aFragmentSource A pointer to the first character of the
       *                        fragment shader.
       */
      Shader(const char* aVertexSource,
             const char* aFragmentSource);

      /**
       * Returns the entirety of the vertex shader.
       *
       * @return A string containing the entire vertex shader.
       */
      const std::string& GetVertexSource() const   { return mVertexSource; }

      /**
       * Returns the entirety of the fragment shader.
       *
       * @return A string containing the entire fragment shader.
       */
      const std::string& GetFragmentSource() const { return mFragmentSource; }

      /**
       * Tells OpenGL to use this shader. This must be called before rendering
       * an object and also before setting any uniforms.
       */
      void Activate() const;

      /**
       * Returns whether a uniform exists in this shader.
       *
       * @param aName The name of the uniform to check.
       * @return True if the uniform exists, false otherwise.
       */
      bool IsUniformDefined(const std::string& aName) const;

      /**
       * Sets a boolean uniform on this shader.
       *
       * @param aName The name of the uniform to set.
       * @param aValue The value to set the uniform to.
       */
      void SetBool(const std::string& aName, bool aValue) const;

      /**
       * Sets an integer uniform on this shader.
       *
       * @param aName The name of the uniform to set.
       * @param aValue The value to set the uniform to.
       */
      void SetInt(const std::string& aName, int aValue) const;

      /**
       * Sets a float uniform on this shader.
       *
       * @param aName The name of the uniform to set.
       * @param aValue The value to set the uniform to.
       */
      void SetFloat(const std::string& aName, float aValue) const;

      /**
       * Sets a vec3 uniform on this shader.
       *
       * @param aName The name of the uniform to set.
       * @param aValue The value to set the uniform to.
       */
      void SetVec3(const std::string& aName, const glm::vec3& aVec) const;

      /**
       * Sets a mat4 uniform on this shader.
       *
       * @param aName The name of the uniform to set.
       * @param aValue The value to set the uniform to.
       */
      void SetMat4(const std::string& aName, const glm::mat4& aMat) const;

    private:

      /**
       * Compiles the vertex/fragment shaders and assigns an ID to each.
       *
       * @param aShaderID The ID to assign to this shader.
       * @param aShaderSource The source code of the shader.
       * @param aShaderType The type of the shader (GL_VERTEX_SHADER,
       *                    GL_FRAGMENT_SHADER, etc.)
       */
      void CompileShader(unsigned int& aShaderID,
                         const std::string& aShaderSource,
                         GLenum aShaderType);

      /**
       * Creates a shader program given the IDs to a vertex shader
       * and a fragment shader. This is done after both shaders have
       * successfully compiled.
       *
       * @param aVertexID The ID of the vertex shader as known to OpenGL.
       * @param aFragmentID The ID of the fragment shader as known to OpenGL.
       */
      void CreateProgram(unsigned int aVertexID,
                         unsigned int aFragmentID);

      std::string mVertexSource;
      std::string mFragmentSource;

      unsigned int mProgramId;
  };
}

#endif
