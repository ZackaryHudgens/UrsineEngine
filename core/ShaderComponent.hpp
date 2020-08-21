#ifndef SHADERCOMPONENT_HPP
#define SHADERCOMPONENT_HPP

#include <string>

#include <GL/glew.h>

#include "GraphicalComponent.hpp"

using core::GraphicalComponent;

namespace core
{
  /**
   * A wrapper class that makes loading/applying GLSL shaders easier.
   */
  class ShaderComponent : public GraphicalComponent
  {
    public:
      ShaderComponent(const std::string& aVertexPath,
                      const std::string& aFragmentPath);
      ~ShaderComponent() { std::cout << "uh" << std::endl; }

      void Update() override {}
      void Render() const override;

      void SetUniform(const std::string& aName,
                      const std::vector<double>& aValueList);

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
