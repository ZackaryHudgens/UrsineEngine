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

void PyExtension::Connect(const std::string& aName,
                                 Observer& aObserver,
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
}
