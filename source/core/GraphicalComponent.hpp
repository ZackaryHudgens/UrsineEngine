#ifndef GRAPHICALCOMPONENT_HPP
#define GRAPHICALCOMPONENT_HPP

#include <memory>

#include "Component.hpp"
#include "Shader.hpp"

namespace core
{
  typedef std::vector<Shader> ShaderList;

  /**
   * A GraphicalComponent is a Component that also requires
   * a Render() function to be defined.
   */
  class GraphicalComponent : public Component
  {
    public:
      GraphicalComponent();

      void Render() const;

      void CreateAndAddShader(const std::string& aVertexPath,
                              const std::string& aFragmentPath);
      const ShaderList& GetShaders() const { return mShaders; }

    private:
      virtual void PrivateRender() const = 0;

      ShaderList mShaders;
  };
}

#endif
