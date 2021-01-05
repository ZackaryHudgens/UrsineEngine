#ifndef ACHIEVEMENTSTRACKER_HPP
#define ACHIEVEMENTSTRACKER_HPP

#include <map>
#include <string>

#include "Observer.hpp"

namespace example_three
{
  /**
   * A class that connects to various signals during construction
   * and awards achievements based on arbitrary conditions.
   *
   * Note that this class inherits from the Observer class; in order
   * to connect to a signal, the object in question must be an Observer.
   * GameObjects and Components are Observers as well.
   */
  class AchievementsTracker : public core::Observer
  {
    public:
      AchievementsTracker();

    private:

      /**
       * A function that "awards an achievement" by displaying whatever
       * congratulatory message is passed to it.
       */
      void AwardAchievement(const std::string& aMessage);

      /**
       * A map of PlayerObject names to the number of times they've pressed
       * the Q key.
       */
      std::map<std::string, int> mQPressMap;
  };
}

#endif
