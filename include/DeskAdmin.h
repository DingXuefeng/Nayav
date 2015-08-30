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
#include "RoundAdmin.h"
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
    void NewRounds();
    void AddBet(const int bet) { Getpool() += bet; }
    void Raise(IPlayer* raiser, const int raise);
  private:
    void Loop();
    int& Getround() { return GetRoundAdmin()->Getround(); }
    int& GetRoundBet() { return GetRoundAdmin()->GetRoundBet(); }
    const int GetRoundBet() const { return GetRoundAdmin()->GetRoundBet(); }
    int& Getpool() { return GetRoundAdmin()->Getpool(); }
    const int Getpool() const { return GetRoundAdmin()->Getpool(); }
    IPlayer *& GetActionPlayer() { return GetRoundAdmin()->GetActionPlayer(); }
    const IPlayer * GetActionPlayer() const { return GetRoundAdmin()->GetActionPlayer(); }
    IPlayer *& GetsmallBlind() { return GetRoundAdmin()->GetsmallBlind(); }
    const IPlayer * GetsmallBlind() const { return GetRoundAdmin()->GetsmallBlind(); }
    IPlayer *& GetbigBlind() { return GetRoundAdmin()->GetbigBlind(); }
    const IPlayer * GetbigBlind() const { return GetRoundAdmin()->GetbigBlind(); }
    Players & GetonDesk() { return GetRoundAdmin()->GetonDesk(); }
    const Players GetonDesk() const { return GetRoundAdmin()->GetonDesk(); }
    //Players & GetonDesk() { return m_onDesk; }
    //const Players GetonDesk() const { return m_onDesk; }

    Players::iterator m_roundsFirstPlayer;
    const Players *m_players;
    IJudger *m_judger;
    Players::const_iterator m_D_player;
    Players m_onDesk;
    Cards m_pubCards;
    std::map<IPlayer*,const Cards*> m_inhands;
    RoundAdmin* m_roundAdmin;

  private:
    const RoundAdmin* GetRoundAdmin() const { return m_roundAdmin; }
    RoundAdmin*& GetRoundAdmin() { return m_roundAdmin; }
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
    Players::iterator& GetCurrentPlayer() { 
      return GetRoundAdmin()->GetCurrentPlayer();
    }
    Players::iterator& GetroundsFirstPlayer() { 
      return GetRoundAdmin()->GetroundsFirstPlayer();
    }
    void Next_OnDesk() { 
      GetRoundAdmin()->Next_OnDesk();
    };
};
#endif
