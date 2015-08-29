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
#include "IDeskAdmin.h"
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
    virtual const int GetRaisedMoney() const = 0;
    const char* GetName() const { return m_name; };
    void Fold() const {};
    void Call() { m_money -= GetDeskAdmin()->GetCurrentRaise(); };
    void Raise(const int money) { 
      GetDeskAdmin()->Raise(this,money);
      m_money -= GetDeskAdmin()->GetCurrentRaise(); 
    };

  private:
//    std::vector<Card*>* m_inhands;
    void JoinDesk(IDeskAdmin* deskadmin) { 
      m_deskadmin = deskadmin; 
      deskadmin->AddPlayer(this);
    };
    IDeskAdmin* GetDeskAdmin() const { return m_deskadmin; };
    IDeskAdmin* m_deskadmin;
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
