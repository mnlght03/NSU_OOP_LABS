#ifndef _STUDENT_LIFE_SIMULATOR_INTERACTIVE_H
#define _STUDENT_LIFE_SIMULATOR_INTERACTIVE_H

class Interactive {
  public:
    Interactive() = default;
    virtual ~Interactive() = default;
    virtual bool Interact(Player &p) const  = 0;
};

#endif  // _STUDENT_LIFE_SIMULATOR_INTERACTIVE_H
