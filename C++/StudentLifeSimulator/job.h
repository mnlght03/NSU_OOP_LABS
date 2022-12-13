#ifndef _STUDENT_LIFE_SIMULATOR_JOB_H
#define _STUDENT_LIFE_SIMULATOR_JOB_H

#include "interactive.h"
#include "player.h"

class Job : public Interactive{
  int salary;
  public:
    Job(int _salary) : salary(_salary) {}
    void Interact(Player& p) const {
      p.addMoney(salary);
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_JOB_H
