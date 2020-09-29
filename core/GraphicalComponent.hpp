#ifndef GRAPHICALCOMPONENT_HPP
#define GRAPHICALCOMPONENT_HPP

#include "Component.hpp"

#include "Shader.hpp"

namespace core
{
  /**
   * A GraphicalComponent is a Component that also requires
   * a Render() function to be defined.
   */
  class GraphicalComponent : public Component
  {
    public:
      GraphicalComponent();

      virtual void Render() const = 0;

      virtual void SetShader(Shader& aShader) { mShader = &aShader; }
      virtual void DisableShader()            { mShader = nullptr; }
      Shader* GetShader() const               { return mShader; }

    private:
      Shader* mShader;
  };
}

#endif
