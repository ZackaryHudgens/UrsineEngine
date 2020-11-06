#include "GraphicalComponent.hpp"

using core::GraphicalComponent;

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

void GraphicalComponent::CreateAndAddShader(const std::string& aVertexPath,
                                            const std::string& aFragmentPath)
{
  mShaders.emplace_back(Shader(aVertexPath, aFragmentPath));

  for(auto& child : GetChildren())
  {
    GraphicalComponent* gc = dynamic_cast<GraphicalComponent*>(child.get());
    if(gc != nullptr)
    {
      gc->CreateAndAddShader(aVertexPath, aFragmentPath);
    }
  }
}
