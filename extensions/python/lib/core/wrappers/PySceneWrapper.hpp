#ifndef SCENEWRAPPER_HPP
#define SCENEWRAPPER_HPP

#include <boost/python.hpp>

#include "Scene.hpp"

namespace bp = boost::python;

using core::GameObject;
using core::Scene;

namespace py
{
  /**
   * A wrapper for the Scene class. Allows Python to add objects
   * without the use of smart pointers.
   */
  class SceneWrapper : public Scene
                     , public bp::wrapper<Scene>
  {
    public:
      SceneWrapper();

      void AddObject_(GameObject& aObject);
  };
}

#endif
