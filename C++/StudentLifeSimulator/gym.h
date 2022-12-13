#ifndef _STUDENT_LIFE_SIMULATOR_GYM_H
#define _STUDENT_LIFE_SIMULATOR_GYM_H

#include "interactive.h"
#include "paid.h"
#include "player.h"

class GymCard : public Paid {
  int duration;
  public:
    GymCard(const int& _cost, const int& _duration) : Paid(_cost), duration(_duration) {}
    GymCard(const GymCard &gymCard) : Paid(gymCard.getCost()) {
      this->duration = gymCard.getDuration();
    }
    ~GymCard() = default;
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
  int moodIncr;
  GymCard gymCard;
  bool requestCard(const Player &p) const {
    return ((!!p.GetObject<GymCard>()));
  }
  public:
    Gym(const int& _healthIncr, const int& _energyDecr, const int& _moodIncr, const GymCard& _gymCard) :
      healthIncr(_healthIncr), energyDecr(_energyDecr),
      moodIncr(_moodIncr), gymCard(_gymCard) {}
    void Interact(Player &p) const final {
        if (!requestCard(p))
          throw std::logic_error("You have no Gym Card");
        p.addHealth(healthIncr);
        p.addEnergy(-energyDecr);
        GymCard *gymCard = p.GetObject<GymCard>();
        gymCard->useCard();
        if (gymCard->isExpired())
          p.RemoveObject<GymCard>();
    }
    void buyCard(Player &p) const {
      if (!this->gymCard.isAffordable(p))
        throw std::logic_error("You don't have enough money for Gym Card");
      p.addMoney(-this->gymCard.getCost());
      p.SetObject(GymCard(gymCard.getCost(), gymCard.getDuration()));
    }
    const GymCard& getCard() const {
      return gymCard;
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_GYM_H
