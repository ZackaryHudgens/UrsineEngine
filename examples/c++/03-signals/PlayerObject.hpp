#ifndef PLAYEROBJECT_HPP
#define PLAYEROBJECT_HPP

#include "GameObject.hpp"
#include "Signal.hpp"

namespace example_three
{
  /**
   * A basic player class. Now it takes a name as an argument during
   * construction.
   */
  class PlayerObject : public core::GameObject
  {
    public:
      PlayerObject(const std::string& aName);

      std::string GetPlayerName() const { return mName; }

    private:
      std::string mName;
  };
}

#endif
