#ifndef GAMEOBJECTWRAPPER_HPP
#define GAMEOBJECTWRAPPER_HPP

#include <boost/python.hpp>

#include "PyVectorWrapper.hpp"

#include "GameObject.hpp"

namespace bp = boost::python;

using core::Component;
using core::GameObject;

namespace py
{
  /**
   * A wrapper for the GameObject class. Allows Python to add
   * children and components without smart pointers.
   */
  class GameObjectWrapper : public GameObject
                          , public bp::wrapper<GameObject>
  {
    public:
      GameObjectWrapper();

      void AddChild_(GameObject& aObject);
      void AddComponent_(Component& aComponent);

      void Scale_(const VectorWrapper& aVector);
      void Translate_(const VectorWrapper& aVector);
      void Rotate_(double aDegrees, const VectorWrapper& aVector);
  };
}

#endif
