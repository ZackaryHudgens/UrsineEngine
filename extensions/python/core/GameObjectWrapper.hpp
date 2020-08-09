#ifndef GAMEOBJECTWRAPPER_HPP
#define GAMEOBJECTWRAPPER_HPP

#include <boost/python.hpp>

#include "GameObject.hpp"

using core::Component;
using core::GameObject;

namespace pyExt
{
  /**
   * A wrapper for the GameObject class. Allows Python to add
   * children and components without smart pointers.
   */
  class GameObjectWrapper : public GameObject
                          , public boost::python::wrapper<GameObject>
  {
    public:
      GameObjectWrapper();

      void AddChild_(GameObject& aObject);
      void AddComponent_(Component& aComponent);
  };
}

#endif
