#ifndef _STUDENT_LIFE_SIMULATOR_PAID_H
#define _STUDENT_LIFE_SIMULATOR_PAID_H

#include "player.h"

class Paid {
  int cost;
  public:
    Paid(int _cost) : cost(_cost) {}
    bool isAffordable(const Player &p) const {
      return p.getMoney() >= cost;
    }
    int getCost() const {
      return cost;
    }
    void setCost(int value) {
      cost = value;
    }
};


#endif  // _STUDENT_LIFE_SIMULATOR_PAID_H