#include <boost/python.hpp>

#include "Environment.hpp"

using namespace boost::python;

using core::Component;
using core::Environment;
using core::GameObject;
using core::Scene;

class ComponentWrapper : public Component,
                         public wrapper<Component>
{
  public:
    ComponentWrapper()
      : Component()
    {
    }

    void Update() override { this->get_override("update")(); }
};

class GameObjectWrapper : public GameObject,
                          public wrapper<GameObject>
{
  public:
    GameObjectWrapper()
      : GameObject()
    {
    }

    void AddChildWrapper(GameObject& aObject)
    {
      std::unique_ptr<GameObject> child;
      child.reset(&aObject);
      AddChild(std::move(child));
    }

    void AddComponentWrapper(Component& aComponent)
    {
      std::unique_ptr<Component> comp;
      comp.reset(&aComponent);
      AddComponent(std::move(comp));
    }
};

class SceneWrapper : public Scene,
                     public wrapper<Scene>
{
  public:
    SceneWrapper(const std::string& aName)
      : Scene(aName)
    {
    }

    void AddObjectWrapper(const std::string& aObjectName,
                          GameObject& aObject)
    {
      std::unique_ptr<GameObject> object;
      object.reset(&aObject);
      AddObject(std::move(object));
    }
};

/**
 * Begin Python module.
 */
BOOST_PYTHON_MODULE(core)
{
  def("createEnvironment", &Environment::GetInstance,
    return_value_policy<reference_existing_object>());

  class_<Environment, boost::noncopyable>("Environment", no_init)
    .def("initialize", &Environment::Initialize)
    .def("loadScene", &Environment::LoadScene)
    .def("run", &Environment::Run);

  class_<ComponentWrapper, boost::noncopyable>("Component")
    .def("update", pure_virtual(&Component::Update));

  class_<GameObjectWrapper, boost::noncopyable>("GameObject")
    .def("addChild", &GameObjectWrapper::AddChildWrapper)
    .def("addComponent", &GameObjectWrapper::AddComponentWrapper);

  class_<SceneWrapper, boost::noncopyable>("Scene", init<std::string>())
    .def("addObject", &SceneWrapper::AddObjectWrapper);
}
