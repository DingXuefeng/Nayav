/***********************************
 * Class: IPlayer
 *
 * Interface for the player action
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef IPlayer_H
#define IPlayer_H
#include <list>
class IDeskAdmin;
class IPlayer {
  public:
    enum Action {
      fold,
      call,
      raise,
      allin
    };
  public:
    virtual void JoinDesk(IDeskAdmin* deskadmin) = 0;
    virtual Action GetAction() const = 0;
    virtual const int GetRaisedMoney() const = 0;
    virtual const char *GetName() const = 0;
    virtual const int GetMoney() const = 0;
    virtual const int GetBet() const = 0;
    virtual void ShowStatus() const = 0;
  public:
    virtual void Fold() const = 0;
    virtual void Call() = 0;
    virtual void Raise(int money) = 0;
    virtual IDeskAdmin* GetDeskAdmin() const = 0;
};
typedef std::list<IPlayer*> Players;
#endif
