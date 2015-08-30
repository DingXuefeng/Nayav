/***********************************
 * Class: Human
 *
 * Class for Human
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Human_H
#define Human_H
#include "Player.h"
#include <iostream>
#include <limits>
#include "shellUI.h"
using namespace std;
class Human : public Player{
  public:
    Action GetAction() const {
      std::cout<<"0 fold // 1 call // 2 raise : "<<std::flush;
      int action_id;
      std::cin>>action_id;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      Action action = static_cast<Action>(action_id);
      return action;
    }
    const int GetRaisedMoney() const { 
      std::cout<<"How much money? :"<<std::flush;
      int money;
      cin>>money;
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      return money; 
    }
  private:
    Human(int money,bool allowSave,int saved,const char *name) : 
      Player(money,allowSave,saved,name) {};
    friend class Users;
  private:
    UI *GetUI() { return shellUI::Get(); };
    std::ostream &GetOs() { return std::cout; };
};
#endif
