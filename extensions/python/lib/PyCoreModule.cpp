#include <boost/python.hpp>

#include "Environment.hpp"
#include "MeshComponent.hpp"
#include "ModelComponent.hpp"
#include "Observer.hpp"
#include "Shader.hpp"

#include "wrappers/PyComponentWrapper.hpp"
#include "wrappers/PyGameObjectWrapper.hpp"
#include "wrappers/PySceneWrapper.hpp"
#include "PyMessenger.hpp"

namespace bp = boost::python;

using core::Environment;
using core::MeshComponent;
using core::ModelComponent;
using core::Observer;
using core::Shader;

using py::ComponentWrapper;
using py::GameObjectWrapper;
using py::Messenger;
using py::SceneWrapper;

namespace
{
  Messenger messengerInstance;

  void Connect(Observer& aObserver, const std::string& aName, bp::object& aFunc)
  {
    messengerInstance.Connect(aObserver, aName, aFunc);
  }

  void Notify(const std::string& aName, bp::list& aArgs)
  {
    messengerInstance.NotifySignal(aName, aArgs);
  }
}

BOOST_PYTHON_MODULE(core)
{
  // Returns the environment instance.
  def("get_or_create_environment", &Environment::GetInstance,
    bp::return_value_policy<bp::reference_existing_object>());

  // Allows the notification of signals via Python.
  def("notify", &Notify);

  // Expose the Environment class.
  bp::class_<Environment, boost::noncopyable>("Environment", bp::no_init)
    .def("create_window", &Environment::CreateWindow)
    .def("load_scene", &Environment::LoadScene)
    .def("run", &Environment::Run);

  // Expose the base Observer class.
  // This is necessary for Components and GameObjects to utilize signals.
  bp::class_<Observer, boost::noncopyable>("Observer")
    .def("connect", &Connect);

  // Expose the Component class.
  bp::class_<ComponentWrapper, bp::bases<Observer>, boost::noncopyable>("Component")
    .def("update", bp::pure_virtual(&Component::Update))
    .def("load", &ComponentWrapper::Load)
    .def("unload", &ComponentWrapper::Unload)
    .def("get_parent", &ComponentWrapper::GetParent, bp::return_internal_reference<>());

  // Expose the GameObject class.
  bp::class_<GameObjectWrapper, bp::bases<Observer>, boost::noncopyable>("GameObject")
    .def("add_child", &GameObjectWrapper::AddChild_)
    .def("add_component", &GameObjectWrapper::AddComponent_)
    .def("scale", &GameObjectWrapper::Scale_)
    .def("translate", &GameObjectWrapper::Translate_)
    .def("rotate", &GameObjectWrapper::Rotate_);

  // Expose the Scene class.
  bp::class_<SceneWrapper, boost::noncopyable>("Scene")
    .def("add_object", &SceneWrapper::AddObject_);

  // Finally, expose a handful of useful predefined components.
  // MeshComponent
  bp::class_<MeshComponent,
             bp::bases<Component>,
             boost::noncopyable>("MeshComponent", bp::no_init)
    .def("update", &MeshComponent::Update)
    .def("render", &MeshComponent::Render);

  // ModelComponent
  bp::class_<ModelComponent,
             bp::bases<Component>,
             boost::noncopyable>("ModelComponent")
    .def("update", &ModelComponent::Update)
    .def("render", &ModelComponent::Render)
    .def("load_model", &ModelComponent::LoadModel);
}
