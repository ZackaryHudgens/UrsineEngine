#include "GraphicalComponent.hpp"

using UrsineRenderer::GraphicalComponent;

GraphicalComponent::GraphicalComponent()
  : Component()
{
}

void GraphicalComponent::AddChild(std::unique_ptr<Component> aChild)
{
  auto* gc = dynamic_cast<GraphicalComponent*>(aChild.get());
  if(gc != nullptr)
  {
    for(const auto& shader : mShaders)
    {
      gc->AddShader(shader);
    }
  }

  Component::AddChild(std::move(aChild));
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

void GraphicalComponent::AddShader(const Shader& aShader)
{
  mShaders.emplace_back(aShader);

  for(auto& child : GetChildren())
  {
    GraphicalComponent* gc = dynamic_cast<GraphicalComponent*>(child.get());
    if(gc != nullptr)
    {
      gc->AddShader(aShader);
    }
  }
}
