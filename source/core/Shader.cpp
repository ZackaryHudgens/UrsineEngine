#include "Shader.hpp"

#include <fstream>
#include <iostream>
#include <sstream>

#include <glm/gtc/type_ptr.hpp>

using core::Shader;

Shader::Shader(const char* aVertexSource,
               const char* aFragmentSource)
  : mProgramId(0)
{
  std::string vertexCodeString = aVertexSource;
  std::string fragmentCodeString = aFragmentSource;

  // Next, compile the shaders.
  unsigned int vertexID, fragmentID;

  CompileShader(vertexID, vertexCodeString, GL_VERTEX_SHADER);
  CompileShader(fragmentID, fragmentCodeString, GL_FRAGMENT_SHADER);

  // Finally, create and link the shader program.
  CreateProgram(vertexID, fragmentID);

  // Delete the shaders as they have been linked and are no longer needed.
  glDeleteShader(vertexID);
  glDeleteShader(fragmentID);
}

void Shader::Activate() const
{
  glUseProgram(mProgramId);
}

void Shader::SetBool(const std::string& aName, bool aValue) const
{
  int loc = glGetUniformLocation(mProgramId, aName.c_str());
  if(loc != -1)
  {
    glUniform1i(loc, (int)aValue);
  }
  else
  {
    std::cout << "Uniform " << aName << " does not exist "
              << "or is reserved!" << std::endl;
  }
}

void Shader::SetInt(const std::string& aName, int aValue) const
{
  int loc = glGetUniformLocation(mProgramId, aName.c_str());
  if(loc != -1)
  {
    glUniform1i(loc, aValue);
  }
  else
  {
    std::cout << "Uniform " << aName << " does not exist "
              << "or is reserved!" << std::endl;
  }
}

void Shader::SetFloat(const std::string& aName, float aValue) const
{
  int loc = glGetUniformLocation(mProgramId, aName.c_str());
  if(loc != -1)
  {
    glUniform1f(loc, aValue);
  }
  else
  {
    std::cout << "Uniform " << aName << " does not exist "
              << "or is reserved!" << std::endl;
  }
}

void Shader::SetMat4(const std::string& aName, const glm::mat4& aMat) const
{
  int loc = glGetUniformLocation(mProgramId, aName.c_str());
  if(loc != -1)
  {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(aMat));
  }
  else
  {
    std::cout << "Uniform " << aName << " does not exist "
              << "or is reserved!" << std::endl;
  }
}

void Shader::CompileShader(unsigned int& aShaderID,
                           const std::string& aShaderSource,
                           GLenum aShaderType)
{
  const char* shaderCode = aShaderSource.c_str();

  // Error variables.
  int success;
  char infoLog[512];

  aShaderID = glCreateShader(aShaderType);
  glShaderSource(aShaderID, 1, &shaderCode, NULL);
  glCompileShader(aShaderID);

  // Check for compile errors.
  glGetShaderiv(aShaderID, GL_COMPILE_STATUS, &success);
  if(!success)
  {
    glGetShaderInfoLog(aShaderID, 512, NULL, infoLog);
    std::cout << "Error compiling shader!\n" << infoLog << std::endl;
  }
}

void Shader::CreateProgram(unsigned int aVertexID,
                           unsigned int aFragmentID)
{
  mProgramId = glCreateProgram();
  glAttachShader(mProgramId, aVertexID);
  glAttachShader(mProgramId, aFragmentID);
  glLinkProgram(mProgramId);

  // Error variables.
  int success;
  char infoLog[512];

  // Check for linking errors.
  glGetProgramiv(mProgramId, GL_LINK_STATUS, &success);
  if(!success)
  {
    glGetProgramInfoLog(mProgramId, 512, NULL, infoLog);
    std::cout << "Error linking program!\n" << infoLog << std::endl;
  }
}
