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
#include "allegro.h"
using namespace std;
class Human : public Player{
  public:
    Action GetAction() const {
      cout<<"0 fold"<<endl
	<<"1 call"<<endl
	<<"2 raise"<<endl;
      int action_id;
      std::cin>>action_id;
      Action action = static_cast<Action>(action_id);
      return action;
    }
    const int GetRaisedMoney() const { 
      cout<<"How much money? :";
      int money;
      cin>>money;
      return money; 
    }
  private:
    Human(int money,bool allowSave,int saved,const char *name) : 
      Player(money,allowSave,saved,name) {};
    friend class Users;
};
#endif
