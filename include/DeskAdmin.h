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
    void AddPlayer(IPlayer *player) { 
      const_cast<Players*>(m_players)->push_back(player); 
    };
    void StartNewDesk();
    const int GetRoundBet() const { return m_roundBet; }
    void Raise(IPlayer* raiser, const int raise);
    void NewRounds();
  private:
    void CheckLoop();
    void RaiseLoop();
    void RoundLoop();
    void PlayerAction();
    void RecordStatus();
    void ShowStatus();
    int m_tmp_roundBet;
    int m_tmp_money;
    int m_tmp_bet;
    Players::iterator m_currentPlayer;
    IPlayer *m_actionPlayer;
    IPlayer *m_firstPlayer;
    Players::iterator m_roundsFirstPlayer;
    IPlayer *m_raiser;
    int m_roundBet;
    const Players *m_players;
    IJudger *m_judger;
    Players::const_iterator m_D_player;
    Players *m_onDesk;

  private:
    void RoundInitialize();
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
