#ifndef SCENEWRAPPER_HPP
#define SCENEWRAPPER_HPP

#include <boost/python.hpp>

#include "Scene.hpp"

using core::GameObject;
using core::Scene;

namespace coreWrappers
{
  /**
   * A wrapper for the Scene class. Allows Python to add objects
   * without the use of smart pointers.
   */
  class SceneWrapper : public Scene
                     , public boost::python::wrapper<Scene>
  {
    public:
      SceneWrapper();

      void AddObject_(GameObject& aObject);
  };
}

#endif
