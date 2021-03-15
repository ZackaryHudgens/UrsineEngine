#ifndef GRAPHICALCOMPONENT_HPP
#define GRAPHICALCOMPONENT_HPP

#include <map>
#include <memory>

#include "Component.hpp"
#include "Shader.hpp"

using UrsineCore::Component;
using UrsineCore::GameObject;

namespace UrsineRenderer
{
  typedef std::map<std::string, Shader> ShaderMap;

  /**
   * A GraphicalComponent is a Component that also contains a Render()
   * function. Inheriting components should override this function
   * to define how to draw them.
   */
  class GraphicalComponent : public Component
  {
    public:
      GraphicalComponent();

      virtual void Render() const {}

      void AddShader(const std::string& aName,
                     const Shader& aShader);
      void RemoveShader(const std::string& aName);

      void SetCurrentShader(const std::string& aName);
      const Shader* GetCurrentShader() const { return mCurrentShader; };

    private:
      ShaderMap mShaderMap;
      Shader* mCurrentShader;
  };
}

#endif
