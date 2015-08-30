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
    void SendInhand();
    void SendPubcards();
    const Cards& GetpubCards() const { return m_pubCards; }
    Cards& GetpubCards() { return m_pubCards; }
    const Inhands& Getinhands() const { return m_inhands; }
    Inhands& Getinhands() { return m_inhands; }
  private:
    Cards m_pubCards;
    Inhands m_inhands;

    Inhands m_fullInhands;
    std::map<IPlayer*,int> m_marks;
    int m_winnerRank;
    Players m_winner;
};
#endif
