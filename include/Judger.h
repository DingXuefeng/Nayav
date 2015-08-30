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
#include "IDeskAdmin.h"
class IPlayer;
class Judger : public IJudger{
  public:
    Judger(IDeskAdmin* deskAdmin) : m_deskAdmin(deskAdmin) {};
    const Players& Judge(const Cards &pub,const Inhands&);
    const std::map<IPlayer*,int>& GetMarks() const { return m_marks; }
    int GetWinnerRank() const { return m_winnerRank; }
    const Players& GetWinners() const { return m_winner; }
    void SendCards();
    void Sendinhands();
    void SendpubCards(int num_pub = 1);
    const Cards& GetpubCards() const { return m_pubCards; }
    Cards& GetpubCards() { return m_pubCards; }
    const Inhands& Getinhands() const { return m_inhands; }
    Inhands& Getinhands() { return m_inhands; }
    void Show() const;
    const Players & GetonDesk() const { return GetDeskAdmin()->GetonDesk(); }

  public:
    const IDeskAdmin *GetDeskAdmin() const { return m_deskAdmin; }
    IDeskAdmin *&GetDeskAdmin() { return m_deskAdmin; }
    void Initialize();
  private:
    Cards m_pubCards;
    Inhands m_inhands;
    IDeskAdmin *m_deskAdmin;

    Inhands m_fullInhands;
    std::map<IPlayer*,int> m_marks;
    int m_winnerRank;
    Players m_winner;
};
#endif
