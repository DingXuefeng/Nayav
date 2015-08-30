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
#include "IPlayer.h"
#include <map>
class IJudger{
  public:
    virtual const Players& Judge(const Cards &pub,const Inhands&) = 0;
    virtual const std::map<IPlayer*,int>& GetMarks() const = 0;
    virtual int GetWinnerRank() const = 0;
    virtual const Players& GetWinners() const = 0;
    virtual const Cards& GetpubCards() const = 0;
    virtual Cards& GetpubCards() = 0;
    virtual const Inhands& Getinhands() const = 0;
    virtual Inhands& Getinhands() = 0;
    virtual void Show() const = 0;
    virtual void SendCards() = 0;
    virtual const IDeskAdmin *GetDeskAdmin() const = 0;
    virtual IDeskAdmin *&GetDeskAdmin() = 0;
    virtual void Initialize() = 0;
};
#endif
