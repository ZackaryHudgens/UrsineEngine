#include "GraphicalComponent.hpp"

using UrsineRenderer::GraphicalComponent;
using UrsineRenderer::Shader;

GraphicalComponent::GraphicalComponent()
  : Component()
{
}

void GraphicalComponent::Render() const
{
  PrivateRender();

  for(const auto& child : GetChildren())
  {
    GraphicalComponent* gc = dynamic_cast<GraphicalComponent*>(child.get());
    if(gc != nullptr)
    {
      gc->Render();
    }
  }
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

const Shader* GraphicalComponent::GetShaderByName(const std::string& aName) const
{
  const Shader* r = nullptr;

  auto s = mShaderMap.find(aName);
  if(s != mShaderMap.end())
  {
    r = &(s->second);
  }

  return r;
}
