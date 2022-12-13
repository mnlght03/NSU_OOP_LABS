#include "player.h"
#include "buff.h"
#include "cafe.h"
#include "composite.h"
#include "consumable.h"
#include "gym.h"
#include "interactive.h"
#include "university.h"
#include "job.h"
#include "menu.h"
#include <iostream>

void startGame();
void printStats(const Player& p);
bool checkStats(const Player& p);
void makeGameStep(Player &p);

const int START_HEALTH = 100;
const int START_INTELLECT = 50;
const int START_MONEY = 50;
const int START_ENERGY = 100;
const int START_HUNGER = 0;
const int START_INFLUENCE = 0;
const int START_MOOD = 50;

const int GAME_STEP_HUNGER_INCR = 10;
const int GAME_STEP_ENERGY_DECR = 10;


int main() {
  startGame();
  return 0;
}

void startGame() {
  Player player(START_HEALTH, START_INTELLECT, START_MONEY,
                START_ENERGY, START_HUNGER, START_INFLUENCE,
                START_MOOD);
  Gym gym(20, 15, 15, GymCard(1000, 10));
  Job job(5000);
  Cafe cafe(Food(500, 30, 25), Coffee(200, IntellectBuff(30, 10), EnergyBuff(30, 10)));
  Bar bar(Food(500, 20, 15), Beer(300, IntellectBuff(-20, 10), EnergyBuff(10, 10), 30));
  University university(20, 15);
  bool gameInProgress = true;
  while(gameInProgress) {
    printStats(player);
    gameInProgress = checkStats(player);
    if (!gameInProgress) {
      std::cout << "\n\tGAME OVER" << std::endl;
      break;
    }
    printMenu(player, gym);
    gameInProgress = processKey(player, gym, job, cafe, bar, university);
    makeGameStep(player);
  }
}

void printStats(const Player& p) {
  std::cout << "Health: " << p.getHealth() << '\n'
            << "Intellect: " << p.getIntellect() << '\n'
            << "Energy: " << p.getEnergy() << '\n'
            << "Hunger: " << p.getHunger() << '\n'
            << "Money: " << p.getMoney() << '\n'
            << "Influence: " << p.getInfluence() << '\n'
            << "Mood: " << p.getMood() << std::endl;
  auto *intellectBuff = p.GetObject<IntellectBuff>();
  auto *energyBuff = p.GetObject<EnergyBuff>();
  std::cout << "Buffs:\n\t";
  if (intellectBuff == nullptr && energyBuff == nullptr)
    std::cout << "None\n";
  if (intellectBuff != nullptr) {
    std::cout << "IntellectBuff:\n\t\t"
              << "Duration: " << intellectBuff->getDuration()
              << "\n\t\tBuff Value: " << intellectBuff->getBuffValue() << "\n";
  }
  if (energyBuff != nullptr) {
    std::cout << "EnergyBuff:\n\t\t"
              << "Duration: " << energyBuff->getDuration()
              << "\n\t\tBuff Value: " << energyBuff->getBuffValue() << "\n";
  }
  auto *gymCard = p.GetObject<GymCard>();
  std::cout << "Gym Card:\n\t";
  if (gymCard == nullptr)
    std::cout << "None\n";
  else {
    std::cout << "Duration: " << gymCard->getDuration() << "\n";
  }
  std::cout << std::endl;
}

bool checkStats(const Player& p) {
  if (p.getHealth() == 0 ||
      p.getEnergy() == 0 ||
      p.getHunger() == 100 ||
      p.getMood() == 0)
    return false;
  return true;
}

void makeGameStep(Player& p) {
  auto *intellectBuff = p.GetObject<IntellectBuff>();
  if (intellectBuff != nullptr) {
    intellectBuff->decrEffect(p);
  }
  auto *energyBuff = p.GetObject<EnergyBuff>();
  if (energyBuff != nullptr) {
    energyBuff->decrEffect(p);
  }
  p.addEnergy(-GAME_STEP_ENERGY_DECR);
  p.addHunger(GAME_STEP_HUNGER_INCR);
}
