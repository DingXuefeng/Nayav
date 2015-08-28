/***********************************
 * Class: Nayav
 *
 * Class for Nayav
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Nayav_H
#define Nayav_H
#include "Player.h"
class Nayav : public Player{
  public:
    Action GetAction() const;
    static Nayav* Me();

  private:
    Nayav() : Player(1000,false,0,"Nayav") {};
    static Nayav* f_Nayav;
};
#endif
