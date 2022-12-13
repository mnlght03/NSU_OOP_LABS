#ifndef _STUDENT_LIFE_SIMULATOR_UNIVERSITY_H
#define _STUDENT_LIFE_SIMULATOR_UNIVERSITY_H

#include "interactive.h"
#include "player.h"

class University : public Interactive {
  int intellectIncr;
  int energyDecr;

  public:
    University(int _intellectIncr, int _energyDecr) : intellectIncr(_intellectIncr), energyDecr(_energyDecr) {}
    void Interact(Player &p) const {
      p.addIntellect(intellectIncr);
      p.addEnergy(-energyDecr);
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_UNIVERSITY_H
