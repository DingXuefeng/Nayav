/***********************************
 * Class: Player
 *
 * Interface for the player action
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Player_H
#define Player_H
#include "IPlayer.h"
#include <vector>
//class Card;
//class Gift;
#include <cstring>
class Player : public IPlayer {
  /*
  public:
    std::vector<Card*>* GetInhands() const { return m_inhands; };
    const int GetMoney() const { return m_money; };
    const bool GetAllowSave() const { return m_allowSave; };
    const std::vector<Gift*>* CheckGift() const { return NULL; };
    void AllocateGift(const int id) {};
    */
  public:
    virtual Action GetAction() const = 0;
    const char* GetName() const { return m_name; };
  private:
//    std::vector<Card*>* m_inhands;
    char m_name[30];
    int m_money;
    bool m_allowSave;
    int m_saved;

  private:
    Player(int money,bool allowSave,int saved,const char *name) : 
      m_money(money),m_allowSave(allowSave),m_saved(saved) {
	memcpy(m_name,name,30);
      };
    friend class Human;
    friend class Nayav;
};
#endif
