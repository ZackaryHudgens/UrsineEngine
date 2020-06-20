#include <boost/python.hpp>

using namespace boost::python;

#include "Environment.hpp"

#include "ComponentWrapper.hpp"
#include "GameObjectWrapper.hpp"
#include "PyExtension.hpp"
#include "SceneWrapper.hpp"
#include "Signal.hpp"

using pyExt::ComponentWrapper;
using pyExt::GameObjectWrapper;
using pyExt::PyExtension;
using pyExt::SceneWrapper;

using core::Environment;

// TESTING
object obj;

void setFunc(const object aFunc)
{
  obj = aFunc;
}

void callFunc(list aArgs)
{
  obj(*tuple(aArgs));
}

/*namespace
{
  Environment& GetOrCreateEnvironment()
  {
    Environment::GetInstance().RegisterExtension<PyExtension>();
    return env;
  }
}*/

BOOST_PYTHON_MODULE(core)
{
  def("setFunc", &setFunc);
  def("callFunc", &callFunc);

  // Expose the Environment class.
  //def("get_or_create_environment", &GetOrCreateEnvironment,
  //  return_value_policy<reference_existing_object>());

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
