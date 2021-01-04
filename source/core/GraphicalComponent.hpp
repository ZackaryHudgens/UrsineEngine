#ifndef GRAPHICALCOMPONENT_HPP
#define GRAPHICALCOMPONENT_HPP

#include <memory>

#include "Component.hpp"
#include "Shader.hpp"

namespace core
{
  typedef std::vector<Shader> ShaderList;

  /**
   * A GraphicalComponent is a Component that also contains a Render()
   * function. Inheriting classes should override the PrivateRender() function
   * to define how to draw them.
   */
  class GraphicalComponent : public Component
  {
    public:
      GraphicalComponent();

      void Render() const;

      virtual void AddChild(std::unique_ptr<Component> aChild) override;

      void AddShader(const char* aVertexSource, const char* aFragmentSource);
      const ShaderList& GetShaders() const { return mShaders; }

    private:
      virtual void PrivateRender() const {};

      ShaderList mShaders;
  };
}

#endif
