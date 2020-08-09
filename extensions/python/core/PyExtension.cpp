#include "PyExtension.hpp"

using pyExt::PyExtension;

PyExtension::PyExtension()
  : Extension()
{
}

void PyExtension::Update()
{
}

void PyExtension::CreateSignal(const std::string& aName)
{
  auto sig = mSignalMap.find(aName);
  if(sig == mSignalMap.end())
  {
    mSignalMap.emplace(aName, pySignal());
  }
}

void PyExtension::NotifySignal(const std::string& aName,
                               boost::python::list& aArgs)
{
  auto sig = mSignalMap.find(aName);
  if(sig != mSignalMap.end())
  {
    sig->second.Notify(aArgs);
  }
}

void PyExtension::Connect(Observer& aObserver,
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
