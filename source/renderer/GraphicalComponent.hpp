#ifndef GRAPHICALCOMPONENT_HPP
#define GRAPHICALCOMPONENT_HPP

#include <map>
#include <memory>

#include "Component.hpp"
#include "Shader.hpp"

using UrsineCore::Component;

namespace UrsineRenderer
{
  typedef std::map<std::string, Shader> ShaderMap;

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

      void AddShader(const std::string& aName,
                     const Shader& aShader);
      void RemoveShader(const std::string& aName);
      const Shader* GetShaderByName(const std::string& aName) const;
      const ShaderMap& GetShaderMap() const { return mShaderMap; }

    private:
      virtual void PrivateRender() const {};

      ShaderMap mShaderMap;
  };
}

#endif
