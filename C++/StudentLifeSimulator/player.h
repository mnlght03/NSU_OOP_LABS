#ifndef _STUDENT_LIFE_SIMULATOR_PLAYER_H
#define _STUDENT_LIFE_SIMULATOR_PLAYER_H

#include "composite.h"
#include <vector>

class GymCard;
class IntellectBuff;
class EnergyBuff;

class Player : public composite::Composite<Player> {
  int health;
  int intellect;
  int money;
  int energy;
  int hunger;
  int influence;
  int mood;
  int sleep_energy_incr = 60;
  int sleep_mood_incr = 40;
  int sleep_hunger_incr = 30;
  public:
    Player(const int& _health, const int& _intellect, const int& _money, const int& _energy, const int& _hunger, const int& _influence, const int& _mood) :
      health(_health), intellect(_intellect), money(_money), energy(_energy), hunger(_hunger), influence(_influence), mood(_mood) {}
    virtual ~Player() {
      this->RemoveObject<GymCard>();
      this->RemoveObject<IntellectBuff>();
      this->RemoveObject<EnergyBuff>();
    }
    int getHealth() const {
      return health;
    }
    int getIntellect() const {
      return intellect;
    }
    int getMoney() const {
      return money;
    }
    int getEnergy() const {
      return energy;
    }
    int getHunger() const {
      return hunger;
    }
    int getInfluence() const {
      return influence;
    }
    int getMood() const {
      return mood;
    }
    int get_sleep_energy_incr() const {
      return sleep_energy_incr;
    }
    int get_sleep_mood_incr() const {
      return sleep_mood_incr;
    }
    int get_sleep_hunger_incr() const {
      return sleep_hunger_incr;
    }
    void set_sleep_energy_incr(const int& val) {
      sleep_energy_incr = val;
    }
    void set_sleep_mood_incr(const int& val) {
      sleep_mood_incr = val;
    }
    void set_sleep_hunger_incr(const int& val) {
      sleep_hunger_incr = val;
    }
    void addHealth(const int& value) {
      health += value;
      if (health < 0) health = 0;
      if (health > 100) health = 100;
    }
    void addIntellect(const int& value) {
      if (intellect > 0 && intellect < 100)
        intellect += value;
      if (intellect < 0) intellect = 0;
      if (intellect > 100) intellect = 100;
    }
    void addMoney(const int& value) {
      money += value;
    }
    void addEnergy(const int& value) {
      energy += value;
      if (energy < 0) energy = 0;
      if (energy > 100) energy = 100;
    }
    void addHunger(const int& value) {
      hunger += value;
      if (hunger < 0) hunger = 0;
      if (hunger > 100) hunger = 100;
    }
    void addInfluence(const int& value) {
      influence += value;
      if (influence < 0) influence = 0;
      if (influence > 100) influence = 100;
    }
    void addMood(const int& value) {
      mood += value;
      if (mood < 0) mood = 0;
      if (mood > 100) mood = 100;
    }
    void Sleep() {
      addEnergy(sleep_energy_incr);
      addHunger(sleep_hunger_incr);
      addMood(sleep_mood_incr);
    }
    bool isIntellectBuffed() const {
      return (!!this->GetObject<IntellectBuff>());
    }
    bool isEnergyBuffed() const {
      return (!!this->GetObject<EnergyBuff>());
    }
};

#endif  // _PLAYER_H
