#ifndef _STUDENT_LIFE_SIMULATOR_BUFF_H
#define _STUDENT_LIFE_SIMULATOR_BUFF_H

#include "player.h"
#include <stdexcept>

class Buff {
  int buffValue;
  int duration;
  int decrCoefficient;
  public:
    Buff(const int& _buffValue, const int& _duration) : buffValue(_buffValue), duration(_duration) {
      decrCoefficient = buffValue % duration == 0 ? buffValue / duration : buffValue / duration + 1;
    }
    Buff(const Buff &buff) : buffValue(buff.getBuffValue()), duration(buff.getDuration()), decrCoefficient(buff.getDecrCoefficient()) {}
    virtual ~Buff() = default;
    void decrDuration() {
      if (duration > 0)
        --duration;
    }
    void decrBuffValue() {
      buffValue -= decrCoefficient;
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
    IntellectBuff(const int& _buffValue, const int& _duration) : Buff(_buffValue, _duration) {}
    IntellectBuff(const IntellectBuff &buff) : Buff(buff.getBuffValue(), buff.getDuration()) {}
    virtual ~IntellectBuff() = default;
    virtual void applyBuff(Player &p) const {
      if (p.isIntellectBuffed())
        throw std::logic_error("Intellect is already buffed");
      p.addIntellect(this->getBuffValue());
      p.SetObject(IntellectBuff(*this));
    }
    virtual void decrEffect(Player &p) {
      if (p.isIntellectBuffed()) {
        auto *playerBuff = p.GetObject<IntellectBuff>();
        p.addIntellect(-playerBuff->getDecrCoefficient());
        playerBuff->decrBuffValue();
        playerBuff->decrDuration();
        if (playerBuff->getDuration() == 0)
          p.RemoveObject<IntellectBuff>();
      }
    }
};

#include <iostream>
class EnergyBuff : public Buff {
  public:
    EnergyBuff(const int& _buffValue, const int& _duration) : Buff(_buffValue, _duration) {}
    EnergyBuff(const EnergyBuff &buff) : Buff(buff.getBuffValue(), buff.getDuration()) {}
    virtual ~EnergyBuff() = default;
    virtual void applyBuff(Player &p) const {
      if (p.isEnergyBuffed())
        throw std::logic_error("Energy is already buffed");
      p.addEnergy(this->getBuffValue());
      p.SetObject(EnergyBuff(*this));
    }
    virtual void decrEffect(Player &p) {
      if (p.isEnergyBuffed()) {
        auto *playerBuff = p.GetObject<EnergyBuff>();
        p.addEnergy(-playerBuff->getDecrCoefficient());
        playerBuff->decrBuffValue();
        playerBuff->decrDuration();
        if (playerBuff->getDuration() == 0)
          p.RemoveObject<EnergyBuff>();
      }
    }
};

#endif  // _STUDENT_LIFE_SIMULATOR_BUFF_H
