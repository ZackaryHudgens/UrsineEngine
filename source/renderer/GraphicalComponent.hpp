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
   * function. Inheriting components should override this function
   * to define how to draw them, typically by using a Shader object.
   */
  class GraphicalComponent : public Component
  {
    public:

      /**
       * Constructor.
       */
      GraphicalComponent();

      /**
       * A virtual function that draws the Component. Should be overridden
       * by inheriting Components to provide visualization.
       */
      virtual void Render() const {}

      /**
       * Adds a Shader to this Component. This fails if a shader with the
       * given name already exists.
       *
       * @param aName The name of the shader.
       * @param aShader The shader object to add.
       * @return True if successful, false otherwise.
       */
      bool AddShader(const std::string& aName,
                     const Shader& aShader);

      /**
       * Removes a Shader from this Component. This fails if a shader with the
       * given name doesn't exist.
       *
       * @param aName The name of the shader to remove.
       * @return True if successful, false otherwise.
       */
      bool RemoveShader(const std::string& aName);

      /**
       * Sets the current Shader to be used in rendering. This fails if
       * no shader with the given name exists.
       *
       * @param aName The name of the Shader to use in rendering.
       * @return True if successful, false otherwise.
       */
      bool SetCurrentShader(const std::string& aName);

      /**
       * Returns the current Shader.
       *
       * @return A pointer to the current Shader, or nullptr if no Shader
       *         has been set or if the current Shader was removed.
       */
      const Shader* GetCurrentShader() const { return mCurrentShader; };

    private:
      ShaderMap mShaderMap;
      Shader* mCurrentShader;
  };
}

#endif
