/***********************************
 * Class: IDeskAdmin
 *
 * Interface for the DeskAdmin action
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef IDeskAdmin_H
#define IDeskAdmin_H
#include "Card.h"
#include <vector>
class IPlayer;
class IJudger;
#include <map>
class IDeskAdmin{
  public:
    enum Round {
      pre_flop,
      flop,
      turn,
      river
    };
  public:
    virtual void AddPlayer(IPlayer *player) = 0;
    virtual void StartNewDesk() = 0;
    virtual const int GetRoundBet() const = 0;
    virtual void Raise(IPlayer* raiser, const int raise) = 0;
    virtual const int GetBlind() const = 0;
  private:
    virtual IJudger* GetJudger() const = 0;
    virtual void SetJudger(IJudger* judger) = 0;
};
#endif
