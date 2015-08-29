/***********************************
 * Class: DeskAdmin
 *
 * Class for DeskAdmin
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef DeskAdmin_H
#define DeskAdmin_H
#include "IDeskAdmin.h"
#include "IPlayer.h"
#include <vector>
#include "Judger.h"
#include <iostream>
using std::cout;
using std::endl;
class DeskAdmin : public IDeskAdmin{
  public:
    void AddPlayer(IPlayer *player) { m_players->push_back(player); };
    void StartNewDesk();
    const int GetRoundBet() const { return m_roundBet; }
    void Raise(IPlayer* raiser, const int raise) { 
      m_raiser = m_currentPlayer; m_roundBet += raise; 
    }
    void NewRounds();
  private:
    Players::iterator m_currentPlayer;
    Players::iterator m_raiser;
    int m_roundBet;
    Players *m_players;
    IJudger *m_judger;
    Players::iterator m_D_player;
    Players *m_onDesk;

  private:
    DeskAdmin() : m_players(new Players), m_judger(new Judger) {};
    friend class Eimer;
    IJudger* GetJudger() const { return m_judger; };
    void SetJudger(IJudger* judger) { m_judger = judger; }
    void Show(const Cards& pub,const std::map<IPlayer*,const Cards*>&) const;
    const int GetBlind() const { return 10; };
    void Next_OnDesk() { 
      ++m_currentPlayer;
      if(!*m_currentPlayer)
	++m_currentPlayer;
    };
};
#endif
