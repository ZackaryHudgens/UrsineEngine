#ifndef ENVIRONMENT_HPP
#define ENVIRONMENT_HPP

#include <map>
#include <memory>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Extension.hpp"
#include "Scene.hpp"

/**
 * Define "env" as a shorthand to get the Envrionment instance.
 */
#ifndef env
#define env core::Environment::GetInstance()
#endif

namespace core
{
  class Environment
  {
    public:
      ~Environment();

      static Environment& GetInstance();

      bool CreateWindow(const char* aTitle, int aWidth, int aHeight);
      void Run();

      void LoadScene(Scene& aScene);

      bool RegisterExtension(const std::string& aName,
                                    std::unique_ptr<Extension> aExtension);
      Extension* GetExtension(const std::string& aName);

    protected:
      Environment();

    private:
      void Update();
      void Render();

      GLFWwindow* mWindow;

      static std::unique_ptr<Environment> mInstance;
      std::map<std::string, std::unique_ptr<Extension>> mExtensionMap;
      Scene* mCurrentScene;

      bool mInitialized;
      int mInternalWidth;
      int mInternalHeight;
  };
}

#endif
