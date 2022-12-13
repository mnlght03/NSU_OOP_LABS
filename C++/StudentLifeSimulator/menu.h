#ifndef _STUDENT_LIFE_SIMULATOR_MENU_H
#define _STUDENT_LIFE_SIMULATOR_MENU_H

#include <iostream>
#include "player.h"
#include "gym.h"
#include "job.h"
#include "cafe.h"
#include "university.h"

void printMenu(const Player& p, const Gym& gym);
bool processKey(Player &p, const Gym& gym, const Job& job,
                const Cafe& cafe, const Bar& bar,
                const University& university);
void printCafeMenu(const Cafe& cafe);
bool processCafeOption(Player &p, const Gym& gym, const Job& job,
                      const Cafe& cafe, const Bar& bar,
                      const University& university);
void printBarMenu(const Bar& bar);
bool processBarOption(Player &p, const Gym& gym, const Job& job,
                      const Cafe& cafe, const Bar& bar,
                      const University& university);

void printMenu(const Player& p, const Gym& gym) {
  std::cout << "1. Go to sleep\n"
            << "2. Go to university\n"
            << "3. Visit cafe\n"
            << "4. Visit a bar\n"
            << "5. Go to work\n";
  auto *gymCard = p.GetObject<GymCard>();
  if (gymCard == nullptr)
    std::cout << "6. Buy Gym Card (" << gym.getCard().getCost() << ")\n";
  else
    std::cout << "6. Go to Gym\n";
  std::cout << "7. Skip\n";
  std::cout << "0. Exit Game";
  std::cout << std::endl;
}

bool processKey(Player &p, const Gym& gym, const Job& job,
                const Cafe& cafe, const Bar& bar,
                const University& university) {
  char key;
  std::cin >> key;
  getchar();
  switch(key) {
      case '1': p.Sleep(); break;
      case '2': university.Interact(p); break;
      case '3':
        printCafeMenu(cafe);
        return processCafeOption(p, gym, job, cafe, bar, university);
      case '4':
        printBarMenu(bar);
        return processBarOption(p, gym, job, cafe, bar, university);
      case '5': job.Interact(p); break;
      case '6':
        if(!p.HasObject<GymCard>()) {
          try {
            gym.buyCard(p);
          } catch (std::exception& err) {
            std::cout << err.what() << std::endl;
            getchar();
          }
        } else {
          gym.Interact(p);
        }
        break;
      case '7': break;
      case '0': return false;
      
      default:
        std::cout << "\tWrong option!" << std::endl;
        printMenu(p, gym);
        return processKey(p, gym, job, cafe, bar, university);
        break;
    }
    return true;
}

void printCafeMenu(const Cafe& cafe) {
  std::cout << "1. Eat food (" << cafe.getFoodCost() << ")\n"
            << "2. Drink coffee (" << cafe.getCoffeeCost() << ")\n"
            << "3. Main Menu";
  std::cout << std::endl;
}

bool processCafeOption(Player &p, const Gym& gym, const Job& job,
                      const Cafe& cafe, const Bar& bar,
                      const University& university) {
  char key;
  std::cin >> key;
  getchar();
  switch(key) {
    case '1':
      try {
        cafe.eatFood(p);
      } catch(std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      break;
    case '2':
      try {
        cafe.drinkCoffee(p);
      } catch(std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      break;
    case '3':
      printMenu(p, gym);
      return processKey(p, gym, job, cafe, bar, university);
    default:
      std::cout << "\tWrong option!" << std::endl;
      printCafeMenu(cafe);
      return processCafeOption(p, gym, job, cafe, bar, university);
  }
  return true;
}

void printBarMenu(const Bar& bar) {
  std::cout << "1. Eat food (" << bar.getFoodCost() << ")\n"
            << "2. Drink beer (" << bar.getBeerCost() << ")\n"
            << "3. Main Menu";
  std::cout << std::endl;
}

bool processBarOption(Player &p, const Gym& gym, const Job& job,
                      const Cafe& cafe, const Bar& bar,
                      const University& university) {
  char key;
  std::cin >> key;
  getchar();
  switch(key) {
    case '1':
      try {
        bar.eatFood(p);
      } catch(std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      break;
    case '2':
      try {
        bar.drinkBeer(p);
      } catch(std::exception& err) {
        std::cout << err.what() << std::endl;
        getchar();
      }
      break;
    case '3':
      printMenu(p, gym);
      return processKey(p, gym, job, cafe, bar, university);
    default:
      std::cout << "\tWrong option!" << std::endl;
      printBarMenu(bar);
      return processBarOption(p, gym, job, cafe, bar, university);
  }
  return true;
}

#endif  // _STUDENT_LIFE_SIMULATOR_MENU_H