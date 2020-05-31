#include <boost/python.hpp>

#include "Environment.hpp"

#include "ComponentWrapper.hpp"
#include "GameObjectWrapper.hpp"
#include "SceneWrapper.hpp"

using namespace boost::python;

using coreWrappers::ComponentWrapper;
using coreWrappers::GameObjectWrapper;
using coreWrappers::SceneWrapper;

using core::Environment;

// TESTING
object obj;

void setFunc(object aFunc)
{
  obj = aFunc;
}

void callFunc(list aArgs)
{
  obj(*tuple(aArgs));
}

/**
 * Begin Python module.
 */
BOOST_PYTHON_MODULE(core)
{
  def("setFunc", &setFunc);
  def("callFunc", &callFunc);

  // Expose the Environment class.
  def("get_or_create_environment", &Environment::GetInstance,
    return_value_policy<reference_existing_object>());

  class_<Environment, boost::noncopyable>("Environment", no_init)
    .def("initialize", &Environment::Initialize)
    .def("load_scene", &Environment::LoadScene)
    .def("run", &Environment::Run);

  // Expose the Component class.
  class_<ComponentWrapper, boost::noncopyable>("Component")
    .def("update", pure_virtual(&Component::Update));

  // Expose the GameObject class.
  class_<GameObjectWrapper, boost::noncopyable>("GameObject")
    .def("add_child", &GameObjectWrapper::AddChild_)
    .def("add_component", &GameObjectWrapper::AddComponent_);

  // Expose the Scene class.
  class_<SceneWrapper, boost::noncopyable>("Scene")
    .def("add_object", &SceneWrapper::AddObject_);
}
