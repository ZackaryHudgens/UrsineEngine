#include <cassert>

#include <boost/python.hpp>

#include "Environment.hpp"
#include "Observer.hpp"

#include "ComponentWrapper.hpp"
#include "GameObjectWrapper.hpp"
#include "PyExtension.hpp"
#include "SceneWrapper.hpp"

using namespace boost::python;

using core::Environment;
using core::Observer;

using pyExt::ComponentWrapper;
using pyExt::GameObjectWrapper;
using pyExt::PyExtension;
using pyExt::SceneWrapper;

namespace
{
  void RegisterPythonExtension()
  {
    bool success = env.RegisterExtension("pyExt",
                                         std::make_unique<PyExtension>());
    assert(success);
  }

  PyExtension* GetPythonExtension()
  {
    auto* ext = env.GetExtension("pyExt");
    PyExtension* pyExt = dynamic_cast<PyExtension*>(ext);

    return pyExt;
  }

  void Connect(Observer& aObserver, const std::string& aName, object& aFunc)
  {
    auto* ext = GetPythonExtension();
    if(ext != nullptr)
    {
      ext->Connect(aObserver, aName, aFunc);
    }
  }

  void Notify(const std::string& aName, list& aArgs)
  {
    auto* ext = GetPythonExtension();
    if(ext != nullptr)
    {
      ext->NotifySignal(aName, aArgs);
    }
  }
}

BOOST_PYTHON_MODULE(core)
{
  // Needs to be called before anything else in Python.
  def("initialize", &RegisterPythonExtension);

  // Returns the environment instance.
  def("get_or_create_environment", &Environment::GetInstance,
    return_value_policy<reference_existing_object>());

  // Allows the notification of signals via Python.
  def("notify", &Notify);

  // Expose the Environment class.
  class_<Environment, boost::noncopyable>("Environment", no_init)
    .def("create_window", &Environment::CreateWindow)
    .def("load_scene", &Environment::LoadScene)
    .def("run", &Environment::Run);

  // Expose the base Observer class.
  // This is necessary for Components and GameObjects to utilize signals.
  class_<Observer, boost::noncopyable>("Observer")
    .def("connect", &Connect);

  // Expose the Component class.
  class_<ComponentWrapper, bases<Observer>, boost::noncopyable>("Component")
    .def("update", pure_virtual(&Component::Update))
    .def("load", &ComponentWrapper::Load)
    .def("unload", &ComponentWrapper::Unload);

  // Expose the GameObject class.
  class_<GameObjectWrapper, bases<Observer>, boost::noncopyable>("GameObject")
    .def("add_child", &GameObjectWrapper::AddChild_)
    .def("add_component", &GameObjectWrapper::AddComponent_);

  // Expose the Scene class.
  class_<SceneWrapper, boost::noncopyable>("Scene")
    .def("add_object", &SceneWrapper::AddObject_);
}
