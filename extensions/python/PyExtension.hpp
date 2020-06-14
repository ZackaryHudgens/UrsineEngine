#ifndef PYEXTENSION_HPP
#define PYEXTENSION_HPP

#include <boost/python.hpp>

#include "Extension.hpp"
#include "Signal.hpp"

using core::ExtensionT;
using core::Observer;
using core::SignalT;

namespace pyExt
{
  // A specialized Signal that takes a list of python objects
  // as an argument.
  typedef SignalT<boost::python::list&> pySignal;

  /**
   * An extension class which creates a Python library, allowing the
   * UrsineEngine to be invoked and ran via Python script.
   */
  class PyExtension : public ExtensionT<PyExtension>
  {
    public:
      PyExtension();

      void Update() override;

      static void CreateSignal(const std::string& aName);
      static void Connect(const std::string& aName,
                          Observer& aObserver,
                          boost::python::object& aFunc);

    private:
      static std::map<std::string, pySignal> mSignalMap;
  };
}

#endif
