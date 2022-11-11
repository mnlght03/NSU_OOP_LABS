#ifndef _STUDENT_LIFE_SIMULATOR_GYM_H
#define _STUDENT_LIFE_SIMULATOR_GYM_H

#include "interactive.h"
#include "paid.h"
#include "player.h"

class GymCard : public Paid {
  int duration;
  public:
    GymCard(int _cost, int _duration) : Paid(_cost), duration(_duration) {}
    GymCard(const GymCard &gymCard) : Paid(gymCard.getCost()) {
      this->duration = gymCard.getDuration();
    }
    ~GymCard();
    int getDuration() const {
      return duration;
    }
    void useCard() {
      duration--;
    }
    bool isExpired() const {
      return duration == 0;
    }
};

class Gym : public Interactive {
  int healthIncr;
  int energyDecr;
  GymCard gymCard;
  bool requestCard(const Player &p) const {
    return (p.gymCard != nullptr);
  }
  public:
    Gym(int _healthIncr, int _energyDecr, GymCard _gymCard) : healthIncr(_healthIncr), energyDecr(_energyDecr), gymCard(_gymCard) {}
    bool Interact(Player &p) const final {
        if (!requestCard(p))
          return false;
        p.addHealth(healthIncr);
        p.addEnergy(-energyDecr);
        p.gymCard->useCard();
        if (p.gymCard->isExpired())
          p.gymCard = nullptr;
    }
    bool buyCard(Player &p, int duration) const {
      if (!this->gymCard.isAffordable(p))
        return false;
      p.addMoney(-this->gymCard.getCost());
      p.gymCard = new GymCard(this->gymCard);
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_GYM_H
