/***********************************
 * Class: IPlayer
 *
 * Interface for the player action
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef IPlayer_H
#define IPlayer_H
#include <vector>
class IPlayer {
  public:
    enum Action {
      fold,
      call,
      raise,
      allin
    };
  public:
    virtual Action GetAction() const = 0;
    virtual const char *GetName() const = 0;
    /*
  public:
    virtual std::vector<Card*>* GetInhands() const = 0;
    virtual const int GetMoney() const = 0;
    virtual const bool GetAllowSave() const =0;
    virtual const std::vector<Gift*>* CheckGift() const = 0;
    virtual void AllocateGift(const int id) = 0;
    */
};
typedef std::vector<IPlayer*> Players;
#endif
