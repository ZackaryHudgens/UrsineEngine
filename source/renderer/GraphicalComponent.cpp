#include "GraphicalComponent.hpp"

#include <algorithm>

using UrsineRenderer::GraphicalComponent;
using UrsineRenderer::Shader;

/******************************************************************************/
GraphicalComponent::GraphicalComponent()
  : Component()
  , mCurrentShader(nullptr)
{
}

/******************************************************************************/
bool GraphicalComponent::AddShader(const std::string& aName,
                                   const Shader& aShader)
{
  bool success = true;

  if(mShaderMap.find(aName) == mShaderMap.end())
  {
    mShaderMap.emplace(aName, aShader);
  }
  else
  {
    success = false;
  }

  return success;
}

/******************************************************************************/
bool GraphicalComponent::RemoveShader(const std::string& aName)
{
  bool success = true;

  auto foundShader = mShaderMap.find(aName);
  if(foundShader != mShaderMap.end())
  {
    // If the current shader is the one being removed,
    // set the current shader to nullptr.
    if(mCurrentShader == &(foundShader->second))
    {
      mCurrentShader = nullptr;
    }

    mShaderMap.erase(aName);
  }
  else
  {
    success = false;
  }

  return success;
}

/******************************************************************************/
bool GraphicalComponent::SetCurrentShader(const std::string& aName)
{
  bool success = true;

  auto shader = mShaderMap.find(aName);
  if(shader != mShaderMap.end())
  {
    mCurrentShader = &(shader->second);
  }
  else
  {
    success = false;
  }

  return success;
}
