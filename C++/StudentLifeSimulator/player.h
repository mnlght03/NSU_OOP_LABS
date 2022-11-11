#ifndef _STUDENT_LIFE_SIMULATOR_PLAYER_H
#define _STUDENT_LIFE_SIMULATOR_PLAYER_H

#include "gym.h"
#include "buff.h"
#include "consumable.h"
#include <vector>

#define INTBUFFIDX 0
#define ENERGYBUFFIDX 1

class Player {
  int health;
  int intellect;
  int money;
  int energy;
  int hunger;
  int influence;
  int mood;
  // 0 - intellectBuff, 1 - energyBuff
  std::vector<Buff*> buffs = std::vector<Buff*>(2);
  // food that player bought in a shop (all should have cost 0)
  std::vector<Food*> foodStorage;
  public:
    GymCard *gymCard;
    Player(int _health, int _intellect, int _money, int _energy, int _hunger, int _influence, int _mood) :
      health(_health), intellect(_intellect), money(_money), energy(_energy), influence(_influence), mood(_mood) {
        gymCard = nullptr;
        std::fill(buffs.begin(), buffs.end(), nullptr);
      }
    ~Player() {
      delete gymCard;
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
    void addHealth(int value) {
      if (health != 0 && health != 100)
        health += value;
    }
    void addIntellect(int value) {
      if (intellect != 0 && intellect != 100)
        intellect += value;
    }
    void addMoney(int value) {
      if (money != 0 && money != 100)
        money += value;
    }
    void addEnergy(int value) {
      if (energy != 0 && energy != 100)
        energy += value;
    }
    void addHunger(int value) {
      if (hunger != 0 && hunger != 100)
        hunger += value;
    }
    void addInfluence(int value) {
      if (influence != 0 && influence != 100)
        influence += value;
    }
    void addMood(int value) {
      if (mood != 0 && mood != 100)
        mood += value;
    }
    Buff* getIntellectBuff() {
      return buffs[INTBUFFIDX];
    }
    Buff* getEnergyBuff() {
      return buffs[ENERGYBUFFIDX];
    }
    bool isIntellectBuffed() {
      return getIntellectBuff() != nullptr;
    }
    bool isEnergyBuffed() {
      return getEnergyBuff() != nullptr;
    }
    void setIntellectBuff(Buff *intellectBuff) {
      buffs[INTBUFFIDX] = intellectBuff;
    }
    void setEnergyBuff(Buff *energyBuff) {
      buffs[ENERGYBUFFIDX] = energyBuff;
    }
};

#endif  // _PLAYER_H
