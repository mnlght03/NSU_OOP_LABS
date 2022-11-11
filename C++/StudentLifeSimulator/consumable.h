#ifndef _STUDENT_LIFE_SIMULATOR_CONSUMABLE_H
#define _STUDENT_LIFE_SIMULATOR_CONSUMABLE_H

#include "player.h"
#include "paid.h"
#include "buff.h"

class Consumable : public Paid {
  public:
    Consumable(int _cost) : Paid(_cost) {}
    virtual ~Consumable() = default;
    virtual bool use(Player &p) = 0;
};

class Food : public Consumable {
  int hungerDecr;
  int moodIncr;
  public:
    Food(int _foodCost, int _hungerDecr, int _moodIncr) :
      Consumable(_foodCost), hungerDecr(_hungerDecr), moodIncr(_moodIncr) {}
    virtual ~Food() = default;
    int getHungerDecr() const {
      return hungerDecr;
    }
    int getMoodIncr() const {
      return moodIncr;
    }
    bool use(Player &p) const {
      if (!isAffordable(p))
        return false;
      p.addMoney(-this->getCost());
      p.addHunger(-this->getHungerDecr());
      p.addMood(this->getMoodIncr());
    }
};

class Coffee : public Consumable{
  Buff *intellectBuff;
  Buff *energyBuff;
  public:
    Coffee(int _cost, int _duration, Buff *intBuff, Buff *enBuff) :
          Consumable(_cost), intellectBuff(intBuff), energyBuff(enBuff) {}
    virtual ~Coffee() = default;
    bool use(Player &p) const {
      if (!isAffordable(p))
        return false;
      intellectBuff->applyBuff(p);
      energyBuff->applyBuff(p);
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_CONSUMABLE_H
