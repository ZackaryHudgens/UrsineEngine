#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <memory>
#include <string>
#include <vector>

#include <glm/glm.hpp>

#include "Component.hpp"
#include "Observer.hpp"
#include "Signal.hpp"

namespace UrsineCore
{
  class GameObject;

  typedef std::map<std::string, std::unique_ptr<GameObject>> ChildMap;
  typedef std::vector<std::unique_ptr<Component>> ComponentList;

  /**
   * A GameObject is essentially just a sack of components.
   * The components themselves are what determine the behavior
   * of the GameObject.
   */
  class GameObject : public Observer
  {
    public:

      /**
       * Constructor.
       *
       * @param aName The name for this GameObject. If this GameObject
       *              is added to a scene that already contains a
       *              GameObject with the same name, this GameObject
       *              won't be added; names should be unique.
       */
      GameObject(const std::string& aName);

      /**
       * Updates all attached Components and children.
       */
      void Update();

      /**
       * Renders all attached GraphicalComponents and children.
       */
      void Render();

      /**
       * Loads all attached Components and children.
       */
      void Load();

      /**
       * Unloads all attached Components and children.
       */
      void Unload();

      /**
       * Returns the name of this GameObject.
       *
       * @return The name of this GameObject.
       */
      std::string GetName() const { return mName; }

      /**
       * Takes ownership of the given GameObject as a child. This fails
       * if a child with the same name already exists.
       *
       * @param aObject The GameObject to add as a child.
       * @return True if successful, false otherwise.
       */
      bool AddChild(std::unique_ptr<GameObject> aObject);

      /**
       * Removes a child GameObject with the given name.
       *
       * @param aName The name of the GameObject to remove.
       * @return True if successful, false otherwise.
       */
      bool RemoveChild(const std::string& aName);

      /**
       * Returns the child GameObject with the given name.
       *
       * @param aName The name of the child to retrieve.
       * @return A pointer to the child GameObject; nullptr if
       *         the child doesn't exist.
       */
      GameObject* GetChild(const std::string& aName) const;

      /**
       * Returns a vector containing all child GameObjects.
       *
       * @return A vector of pointers to children GameObjects.
       */
      std::vector<GameObject*> GetChildren();

      /**
       * Returns a vector containing pointers to all child
       * GameObjects of a given type.
       *
       * @return A vector of pointers to children GameObjects.
       */
      template<typename T>
      std::vector<T*> GetChildrenOfType() const
      {
        std::vector<T*> children;

        for(const auto& obj : mChildren)
        {
          T* castObj = dynamic_cast<T*>(obj.second.get());
          if(castObj != nullptr)
          {
            children.emplace_back(castObj);
          }
        }

        return children;
      }

      /**
       * Takes ownership of the given Component.
       *
       * @param aComponent The Component to add to this GameObject.
       */
      void AddComponent(std::unique_ptr<Component> aComponent);

      /**
       * Returns a vector containing all Components.
       *
       * @return A vector of pointers to all attached Components.
       */
      std::vector<Component*> GetComponents();

      /**
       * Returns a vector containing pointers to all components
       * of a given type.
       */
      template<typename T>
      std::vector<T*> GetComponentsOfType() const
      {
        std::vector<T*> components;

        for(const auto& comp : mComponents)
        {
          T* castComp = dynamic_cast<T*>(comp.get());
          if(castComp != nullptr)
          {
            components.emplace_back(castComp);
          }
        }

        return components;
      };

      /**
       * Returns a matrix containing all transformations that have been applied
       * to this object.
       *
       * @return A transformation matrix for this object.
       */
      glm::mat4 GetTransform() const;

      /**
       * Returns a vector representing this object's position in 3D space
       * by multiplying it with its transformation matrix.
       *
       * @return This object's position in 3D space.
       */
      glm::vec3 GetPosition() const;

      /**
       * Scales the GameObject's transform by the given amount.
       *
       * @param aScalar The amount to scale by on each axis.
       */
      virtual void Scale(const glm::vec3& aScalar);

      /**
       * Translates this GameObject's transform in the given direction.
       *
       * @param aVector The vector to translate to.
       */
      virtual void Translate(const glm::vec3& aVector);

      /**
       * Rotates this GameObject's transform by the given amount around
       * the given axis.
       *
       * @param aDegrees The amount to rotate by in degrees.
       * @param aAxis The axis around which to rotate.
       */
      virtual void Rotate(double aDegrees,
                          const glm::vec3& aAxis);

      /**
       * Creates a new scalar transform for this GameObject.
       *
       * @param aScalar The amount to scale by on each axis.
       */
      virtual void SetScale(const glm::vec3& aScalar);

      /**
       * Sets the position of this GameObject by creating a new translation
       * transform.
       *
       * @param aVector The position to move to.
       */
      virtual void SetPosition(const glm::vec3& aVector);

      /**
       * Creates a new rotation transform for this GameObject using the given
       * axis of rotation.
       *
       * @param aDegrees The amount to rotate by in degrees.
       * @param aAxis The axis around which to rotate.
       */
      virtual void SetRotation(double aDegrees,
                               const glm::vec3& aAxis);

    private:
      std::string mName;

      ChildMap mChildren;
      ComponentList mComponents;

      glm::mat4 mScalarTransform;
      glm::mat4 mRotationTransform;
      glm::mat4 mTranslationTransform;
  };

  /**
   * GameObject Signals.
   */
  typedef UrsineCore::SignalT<GameObject*> ObjectScaledSignal;
  typedef UrsineCore::SignalT<GameObject*> ObjectMovedSignal;
  typedef UrsineCore::SignalT<GameObject*> ObjectRotatedSignal;

  extern ObjectScaledSignal ObjectScaled;
  extern ObjectMovedSignal ObjectMoved;
  extern ObjectRotatedSignal ObjectRotated;
}

#endif
