#include "Messenger.hpp"

using py::Messenger;;

Messenger::Messenger()
{
}

void Messenger::CreateSignal(const std::string& aName)
{
  auto sig = mSignalMap.find(aName);
  if(sig == mSignalMap.end())
  {
    mSignalMap.emplace(aName, pySignal());
  }
}

void Messenger::NotifySignal(const std::string& aName,
                             boost::python::list& aArgs)
{
  auto sig = mSignalMap.find(aName);
  if(sig != mSignalMap.end())
  {
    sig->second.Notify(aArgs);
  }
}

void Messenger::Connect(Observer& aObserver,
                        const std::string& aName,
                        boost::python::object& aFunc)
{
  auto funcWrapper = [aFunc](boost::python::list& aArgs)
  {
    aFunc(*boost::python::tuple(aArgs));
  };

  auto sig = mSignalMap.find(aName);
  if(sig != mSignalMap.end())
  {
    sig->second.Connect(aObserver, funcWrapper);
  }
  else
  {
    CreateSignal(aName);
    Connect(aObserver, aName, aFunc);
  }
}
