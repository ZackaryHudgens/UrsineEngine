#ifndef COMPONENTWRAPPER_HPP
#define COMPONENTWRAPPER_HPP

#include <boost/python.hpp>

#include "Component.hpp"

namespace bp = boost::python;

using core::Component;

namespace py
{
  /**
  * A wrapper for the Component class. Allows Python script to
  * create new Component classes and override the Update(),
  * Load() and Unload() functions.
  */
  class ComponentWrapper : public Component
                         , public bp::wrapper<Component> 
  {
    public:
      ComponentWrapper();

      void Update() override;

      void Load() override;
      void Unload() override;
  };
}

#endif
