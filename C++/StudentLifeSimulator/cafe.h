#ifndef _STUDENT_LIFE_SIMULATOR_CAFE_H
#define _STUDENT_LIFE_SIMULATOR_CAFE_H

#include "interactive.h"
#include "player.h"
#include "consumable.h"

class BaseCafe : public Interactive {
  Consumable *food;
  public:
    BaseCafe(Consumable *f) : food(f) {}
    virtual ~BaseCafe() = default;
    bool getDrink(Player &p, Consumable *drink) const {
      if (!drink->isAffordable(p))
        return false;
      drink->use(p);
    }
    bool eatFood(Player &p, Consumable *food) const {
      if (!food->isAffordable(p))
        return false;
      food->use(p);
    }
    // Interact() that allows you to make friends
};

class Cafe : public BaseCafe {
  Consumable *coffee;
  Consumable *tea;
  public:
    Cafe(Consumable *f, Consumable *c, Consumable *t) : BaseCafe(f), coffee(c), tea(t) {}
};

class Bar : public BaseCafe {
  Consumable *beer;
  public:
    Bar(Consumable *f, Consumable *b) : BaseCafe(f), beer(b) {}
};

#endif  // _STUDENT_LIFE_SIMULATOR_CAFE_H
