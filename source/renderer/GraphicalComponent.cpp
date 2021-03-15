#include "GraphicalComponent.hpp"

#include <algorithm>

using UrsineRenderer::GraphicalComponent;
using UrsineRenderer::Shader;

GraphicalComponent::GraphicalComponent()
  : Component()
  , mCurrentShader(nullptr)
{
}

void GraphicalComponent::AddShader(const std::string& aName,
                                   const Shader& aShader)
{
  mShaderMap.emplace(aName, aShader);
}

void GraphicalComponent::RemoveShader(const std::string& aName)
{
  mShaderMap.erase(aName);
}

void GraphicalComponent::SetCurrentShader(const std::string& aName)
{
  auto shader = mShaderMap.find(aName);
  if(shader != mShaderMap.end())
  {
    mCurrentShader = &(shader->second);
  }
  else
  {
    mCurrentShader = nullptr;
  }
}
