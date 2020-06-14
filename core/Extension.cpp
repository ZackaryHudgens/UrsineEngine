#include "Extension.hpp"

#include <cassert>

using core::Extension;
using core::ExtensionT;

Extension::Extension()
{
}

template <typename T>
bool ExtensionT<T>::mInitialized = false;

template <typename T>
ExtensionT<T>::ExtensionT()
  : Extension()
{
  assert(mInitialized);
  mInitialized = true;
}
