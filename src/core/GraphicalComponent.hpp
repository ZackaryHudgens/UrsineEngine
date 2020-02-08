#ifndef GRAPHICALCOMPONENT_HPP
#define GRAPHICALCOMPONENT_HPP

#include "Component.hpp"

namespace gCore
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
  };
}

#endif
