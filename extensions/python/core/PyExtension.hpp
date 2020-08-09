#ifndef PYEXTENSION_HPP
#define PYEXTENSION_HPP

#include <boost/python.hpp>

#include "Extension.hpp"
#include "Signal.hpp"

using core::Extension;
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
  class PyExtension : public Extension
  {
    public:
      PyExtension();

      void Update() override;

      void CreateSignal(const std::string& aName);
      void NotifySignal(const std::string& aName,
                        boost::python::list& aArgs);

      void Connect(Observer& aObserver,
                   const std::string& aName,
                   boost::python::object& aFunc);

    private:
      std::map<std::string, pySignal> mSignalMap;
  };
}

#endif
