#ifndef _STUDENT_LIFE_SIMULATOR_BUFF_H
#define _STUDENT_LIFE_SIMULATOR_BUFF_H

#include "player.h"

class Buff {
  int duration;
  int decrCoefficient;
  int buffValue;
  public:
    Buff(int _buffValue, int _duration, int _coefficient) : buffValue(_buffValue), duration(_duration), decrCoefficient(_coefficient) {}
    Buff(const Buff &buff) : buffValue(buff.getBuffValue()), duration(buff.getDuration()), decrCoefficient(buff.getDecrCoefficient()) {}
    virtual ~Buff() = default;
    void decrDuration() {
      --duration;
    }
    bool isExpired() const {
      return duration == 0;
    }
    int getBuffValue() const {
      return buffValue;
    }
    int getDuration() const {
      return duration;
    }
    int getDecrCoefficient() const {
      return decrCoefficient;
    }
    virtual void applyBuff(Player &p) const = 0;
    virtual void decrEffect(Player &p) = 0;
};

class IntellectBuff : public Buff {
  public:
    IntellectBuff(int _buffValue, int _duration, int _coefficient) : Buff(_buffValue, _duration, _coefficient) {}
    IntellectBuff(const IntellectBuff &buff) : Buff(buff.getBuffValue(), buff.getDuration(), buff.getDecrCoefficient()) {}
    virtual ~IntellectBuff() = default;
    virtual void applyBuff(Player &p) const {
      p.addIntellect(this->getBuffValue());
      p.setIntellectBuff(new IntellectBuff(*this));
    }
    virtual void decrEffect(Player &p) {
      if (p.isIntellectBuffed()) {
        p.addIntellect(-this->getDecrCoefficient());
        this->decrDuration();
      }
    }
};

class EnergyBuff : public Buff {
  public:
    EnergyBuff(int _buffValue, int _duration, int _coefficient) : Buff(_buffValue, _duration, _coefficient) {}
    EnergyBuff(const EnergyBuff &buff) : Buff(buff.getBuffValue(), buff.getDuration(), buff.getDecrCoefficient()) {}
    virtual ~EnergyBuff() = default;
    virtual void applyBuff(Player &p) const {
      p.addEnergy(this->getBuffValue());
      p.setEnergyBuff(new EnergyBuff(*this));
    }
    virtual void decrEffect(Player &p) {
      if (p.isEnergyBuffed()) {
        p.addEnergy(-this->getDecrCoefficient());
        this->decrDuration();
      }
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_BUFF_H
