#ifndef COMPONENTWRAPPER_HPP
#define COMPONENTWRAPPER_HPP

#include <boost/python.hpp>

#include "Component.hpp"

using core::Component;

namespace coreWrappers
{
  /**
  * A wrapper for the Component class. Allows Python script to
  * create new Component classes and override the Update(),
  * Load() and Unload() functions.
  */
  class ComponentWrapper : public Component
                         , public boost::python::wrapper<Component> 
  {
    public:
      ComponentWrapper();

      void Update() override;

      void Load() override;
      void Unload() override;
  };
}

#endif
