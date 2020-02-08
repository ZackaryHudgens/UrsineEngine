#ifndef COREOBSERVER_HPP
#define COREOBSERVER_HPP

#include "Animation.hpp"
#include "Callback.hpp"

using gCore::Animation;

namespace gCore
{
  class CoreObserver
  {
    public:
      CoreObserver();

      typedef Callback<const Animation&> animationAdvancedCallback;
      static animationAdvancedCallback AnimationAdvanced;
  };
}

#endif
