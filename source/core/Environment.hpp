#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Scene.hpp"
#include "Signal.hpp"

/**
 * Define "env" as a shorthand to get the Envrionment instance.
 */
#ifndef env
#define env UrsineCore::Environment::GetInstance()
#endif

namespace UrsineCore
{
  /**
   * A singleton class that handles creating a valid OpenGL context,
   * a window, and manages scene updating, loading, and unloading.
   */
  class Environment
  {
    public:
      ~Environment();

      static Environment& GetInstance();

      void Run();

      bool CreateWindow(const std::string& aTitle, int aWidth, int aHeight);
      GLFWwindow* GetWindow() const { return mWindow; }

      double GetTime() const { return glfwGetTime(); }

      void LoadScene(Scene& aScene);
      Scene* GetCurrentScene() { return mCurrentScene; }

    protected:
      Environment();

    private:
      void Update();
      void Render();

      GLFWwindow* mWindow;

      static std::unique_ptr<Environment> mInstance;
      Scene* mCurrentScene;

      bool mInitialized;
      int mInternalWidth;
      int mInternalHeight;
  };
}

#endif
