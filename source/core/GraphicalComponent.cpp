#include "GraphicalComponent.hpp"

using core::GraphicalComponent;

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
      gc->AddShader(shader.GetVertexSource().c_str(),
                    shader.GetFragmentSource().c_str());
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

void GraphicalComponent::AddShader(const char* aVertexSource,
                                   const char* aFragmentSource)
{
  mShaders.emplace_back(Shader(aVertexSource, aFragmentSource));

  for(auto& child : GetChildren())
  {
    GraphicalComponent* gc = dynamic_cast<GraphicalComponent*>(child.get());
    if(gc != nullptr)
    {
      gc->AddShader(aVertexSource, aFragmentSource);
    }
  }
}
