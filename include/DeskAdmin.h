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
class RoundAdmin;
class DeskAdmin : public IDeskAdmin{
  public:
    void AddPlayer(IPlayer *player) { 
      const_cast<Players*>(m_players)->push_back(player); 
    };
    void StartNewDesk();
    const int GetRoundBet() const { return m_roundBet; }
    void Raise(IPlayer* raiser, const int raise);
    void NewRounds();
    void AddBet(const int bet) { m_pool += bet; }
  private:
    void BlindAction();
    void CheckLoop();
    void RaiseLoop();
    void Loop();
    void PlayerAction();
    void RecordStatus();
    void ShowStatus();
    int m_tmp_roundBet;
    int m_tmp_money;
    int m_tmp_bet;
    int m_tmp_pool;
    int m_round;
    int m_pool;
    Players::iterator m_currentPlayer;
    IPlayer *m_actionPlayer;
    IPlayer *m_smallBlind;
    IPlayer *m_bigBlind;
    IPlayer *m_firstPlayer;
    Players::iterator m_roundsFirstPlayer;
    IPlayer *m_raiser;
    int m_roundBet;
    const Players *m_players;
    IJudger *m_judger;
    Players::const_iterator m_D_player;
    Players *m_onDesk;
    Cards m_pubCards;
    std::map<IPlayer*,const Cards*> m_inhands;
    RoundAdmin* m_roundAdmin;

  private:
    void RoundInitialize();
    void SendInhand();
    void FirstRoundLoop();
    void RoundLoop(const int num_pub = 1);
    DeskAdmin() : m_players(new Players), m_judger(new Judger) {};
    friend class Eimer;
    IJudger* GetJudger() const { return m_judger; };
    void SetJudger(IJudger* judger) { m_judger = judger; }
    void Show(const Cards& pub,const std::map<IPlayer*,const Cards*>&) const;
    const bool IsBlind() const;
    const int GetBlind() const { return 10; };
    Players::iterator& GetCurrentPlayer() { return m_currentPlayer; }
    void Next_OnDesk() { 
      ++GetCurrentPlayer();
      if(GetCurrentPlayer() == m_onDesk->end())
	GetCurrentPlayer() = m_onDesk->begin();
    };
};
#endif
