/***********************************
 * Class: Judger
 *
 * Class for Judger
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Judger_H
#define Judger_H
#include "IJudger.h"
#include "IPlayer.h"
#include "IJudger.h"
#include <vector>
class User;
class Judger : public IJudger{
  public:
    IPlayer* Judge(const Cards &pub,const Inhands&);
};
#endif
