#ifndef _STUDENT_LIFE_SIMULATOR_CAFE_H
#define _STUDENT_LIFE_SIMULATOR_CAFE_H

#include "interactive.h"
#include "player.h"
#include "consumable.h"

class BaseCafe {
  Food food;
  public:
    BaseCafe(Food f) : food(f) {}
    virtual ~BaseCafe() = default;
    void eatFood(Player &p) const {
      if (!food.isAffordable(p))
        throw std::logic_error("You don't have enough money");
      food.use(p);
    }
    int getFoodCost() const {
      return food.getCost();
    }
    // TODO: Interact() that allows you to make friends
};

class Cafe : public BaseCafe {
  Coffee coffee;
  public:
    Cafe(const Food& f, const Coffee& c) : BaseCafe(f), coffee(c) {}
    void drinkCoffee(Player &p) const {
      if (!coffee.isAffordable(p))
        throw std::logic_error("You don't have enough money");
      coffee.use(p);
    }
    int getCoffeeCost() const {
      return coffee.getCost();
    }
};

class Bar : public BaseCafe {
  Beer beer;
  public:
    Bar(const Food& f, const Beer& b) : BaseCafe(f), beer(b) {}
    void drinkBeer(Player &p) const {
      if (!beer.isAffordable(p))
        throw std::logic_error("You don't have enough money");
      beer.use(p);
    }
    int getBeerCost() const {
      return beer.getCost();
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_CAFE_H
