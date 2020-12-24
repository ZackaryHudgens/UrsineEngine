#include "PyMessenger.hpp"

using py::Messenger;

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
                             bp::list& aArgs)
{
  auto sig = mSignalMap.find(aName);
  if(sig != mSignalMap.end())
  {
    sig->second.Notify(aArgs);
  }
}

void Messenger::Connect(Observer& aObserver,
                        const std::string& aName,
                        bp::object& aFunc)
{
  auto funcWrapper = [aFunc](bp::list& aArgs)
  {
    aFunc(*bp::tuple(aArgs));
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
