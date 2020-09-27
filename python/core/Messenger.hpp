#ifndef MESSENGER_HPP
#define MESSENGER_HPP

#include <boost/python.hpp>

#include "Signal.hpp"

using core::Observer;
using core::SignalT;

namespace py
{
  // A specialized Signal that takes a list of python objects
  // as an argument.
  typedef SignalT<boost::python::list&> pySignal;

  /**
   * A class that handles the creation and notification of python Signals.
   */
  class Messenger
  {
    public:
      Messenger();

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
