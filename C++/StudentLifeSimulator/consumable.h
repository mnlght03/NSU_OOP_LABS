#ifndef _STUDENT_LIFE_SIMULATOR_CONSUMABLE_H
#define _STUDENT_LIFE_SIMULATOR_CONSUMABLE_H

#include "player.h"
#include "paid.h"
#include "buff.h"
#include <iostream>
#include <stdexcept>

class Consumable : public Paid {
  public:
    Consumable(const int& _cost) : Paid(_cost) {}
    virtual ~Consumable() = default;
    virtual void use(Player &p) const = 0;
};

class Food : public Consumable {
  int hungerDecr;
  int moodIncr;
  public:
    Food(const int& _foodCost, const int& _hungerDecr, const int& _moodIncr) :
      Consumable(_foodCost), hungerDecr(_hungerDecr), moodIncr(_moodIncr) {}
    virtual ~Food() = default;
    int getHungerDecr() const {
      return hungerDecr;
    }
    int getMoodIncr() const {
      return moodIncr;
    }
    virtual void use(Player &p) const {
      if (!isAffordable(p))
        throw std::logic_error("You don't have enough money");
      p.addMoney(-this->getCost());
      p.addHunger(-this->getHungerDecr());
      p.addMood(this->getMoodIncr());
    }
};

class Coffee : public Consumable{
  IntellectBuff intellectBuff;
  EnergyBuff energyBuff;
  public:
    Coffee(const int& _cost, const IntellectBuff& intBuff, const EnergyBuff& enBuff) :
          Consumable(_cost), intellectBuff(intBuff), energyBuff(enBuff) {}
    virtual ~Coffee() = default;
    void use(Player &p) const {
      if (!isAffordable(p))
        throw std::logic_error("You don't have enough money");
      try {
        intellectBuff.applyBuff(p);
      } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      try {
        energyBuff.applyBuff(p);
      } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
    }
};

class Beer : public Consumable{
  IntellectBuff intellectBuff;
  EnergyBuff energyBuff;
  int moodIncrease;
  public:
    Beer(const int& _cost, const IntellectBuff& intBuff, const EnergyBuff& enBuff, const int& moodIncr) :
          Consumable(_cost), intellectBuff(intBuff), energyBuff(enBuff), moodIncrease(moodIncr) {}
    virtual ~Beer() = default;
    void use(Player &p) const {
      if (!isAffordable(p))
        throw std::logic_error("You don't have enough money");
      try {
        intellectBuff.applyBuff(p);
      } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      try {
        energyBuff.applyBuff(p);
      } catch (std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      p.addMood(moodIncrease);
    }
};


#endif  // _STUDENT_LIFE_SIMULATOR_CONSUMABLE_H
