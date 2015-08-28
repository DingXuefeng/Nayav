/***********************************
 * Class: IJudger
 *
 * Interface for the DeskAdmin action
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef IJudger_H
#define IJudger_H
#include "Card.h"
#include <vector>
class IPlayer;
#include <map>
class IJudger{
  public:
    virtual IPlayer* Judge(const Cards &pub,const std::map<IPlayer*,const Cards*>&) = 0;
};
#endif
