#ifndef EXTENSION_HPP
#define EXTENSION_HPP

namespace core
{
  /**
   * This Extension class is an implementation of the Curiously Recurring
   * Template Pattern (CRTP). Extension classes should derive from ExtensionT
   * as follows:
   *
   * class NewExtension : public ExtensionT<NewExtension>
   * {
   *   public:
   *     void Update() override {}
   * };
   *
   * This pattern allows each derived ExtensionT class to create its own
   * Update() logic while also having its own instance of the static variable
   * mInitialized.
   */
  class Extension
  {
    public:
      Extension();

      virtual void Update() = 0;
  };

  /**
   * Each ExtensionT can only be created once; mInitialized is checked and
   * set to true in the constructor.
   */
  template <typename T>
  class ExtensionT : public Extension
  {
    public:
      ExtensionT();

    private:
      static bool mInitialized;
  };
}

#endif
