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
    const Players& Judge(const Cards &pub,const Inhands&);
    const std::map<IPlayer*,int>& GetMarks() const { return m_marks; }
    int GetWinnerRank() const { return m_winnerRank; }
    const Players& GetWinners() const { return m_winner; }
  private:
    Inhands m_fullInhands;
    std::map<IPlayer*,int> m_marks;
    int m_winnerRank;
    Players m_winner;
};
#endif
