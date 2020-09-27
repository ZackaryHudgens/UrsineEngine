#include <cassert>

#include <boost/python.hpp>

#include "Environment.hpp"
#include "MeshComponent.hpp"
#include "ModelComponent.hpp"
#include "Observer.hpp"
#include "Shader.hpp"

#include "ComponentWrapper.hpp"
#include "GameObjectWrapper.hpp"
#include "GraphicalComponentWrapper.hpp"
#include "Messenger.hpp"
#include "SceneWrapper.hpp"

using namespace boost::python;

using core::Environment;
using core::MeshComponent;
using core::ModelComponent;
using core::Observer;
using core::Shader;

using py::ComponentWrapper;
using py::GameObjectWrapper;
using py::GraphicalComponentWrapper;
using py::Messenger;
using py::SceneWrapper;

namespace
{
  Messenger messengerInstance;

  void Connect(Observer& aObserver, const std::string& aName, object& aFunc)
  {
    messengerInstance.Connect(aObserver, aName, aFunc);
  }

  void Notify(const std::string& aName, list& aArgs)
  {
    messengerInstance.NotifySignal(aName, aArgs);
  }
}

BOOST_PYTHON_MODULE(core)
{
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

  // Expose the Shader class, for use with GraphicalComponents.
  class_<Shader>("Shader", init<std::string, std::string>());

  // Expose the GraphicalComponent class.
  class_<GraphicalComponentWrapper,
         bases<ComponentWrapper>,
         boost::noncopyable>("GraphicalComponent")
    .def("set_shader", &GraphicalComponentWrapper::SetShader_)
    .def("disable_shader", &GraphicalComponentWrapper::DisableShader_);

  // Expose the GameObject class.
  class_<GameObjectWrapper, bases<Observer>, boost::noncopyable>("GameObject")
    .def("add_child", &GameObjectWrapper::AddChild_)
    .def("add_component", &GameObjectWrapper::AddComponent_);

  // Expose the Scene class.
  class_<SceneWrapper, boost::noncopyable>("Scene")
    .def("add_object", &SceneWrapper::AddObject_);

  // Lastly, expose a few common, predefined component classes:
  // MeshComponent
  class_<MeshComponent,
         bases<GraphicalComponentWrapper>,
         boost::noncopyable>("MeshComponent", no_init);

  // ModelComponent
  class_<ModelComponent,
}
