#ifndef GRAPHICALCOMPONENTWRAPPER_HPP
#define GRAPHICALCOMPONENTWRAPPER_HPP

#include <boost/python.hpp>

#include "GraphicalComponent.hpp"

using boost::python::wrapper;

using core::GraphicalComponent;
using core::Shader;

namespace py
{
  /**
   * A wrapper for the GraphicalComponent class. This should probably
   * never be used directly in Python script; it only exists to provide
   * a common interface for other GraphicalComponents.
   */
  class GraphicalComponentWrapper : public GraphicalComponent
                                  , public wrapper<GraphicalComponent>
  {
    public:
      GraphicalComponentWrapper();

      void Update() override;
      void Render() const override;
  };
}

#endif
