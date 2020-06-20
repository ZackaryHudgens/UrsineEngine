#ifndef EXTENSION_HPP
#define EXTENSION_HPP

namespace core
{
  /**
   * A class that provides basic extension capabilities. Each child class
   * needs to provide its own Update() logic.
   *
   * Extensions are registered via Environment::RegisterExtension().
   */
  class Extension
  {
    public:
      Extension();

      virtual void Update() = 0;
  };
}

#endif
