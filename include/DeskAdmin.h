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
class DeskAdmin : public IDeskAdmin{
  public:
    void AddPlayer(IPlayer *player) { m_players->push_back(player); };
    void StartNewDesk();
    const int GetCurrentRaise() const { return m_currentRaise; }
    void Raise(IPlayer* raiser, const int raise) { 
      m_raiser = raiser; m_currentRaise += raise; 
    }
    void NewRounds();
  private:
    IPlayer* m_raiser;
    int m_currentRaise;
    Players *m_players;
    IJudger *m_judger;
    IPlayer* m_D_player;

  private:
    DeskAdmin() : m_players(new Players), m_judger(new Judger) {};
    friend class Eimer;
    IJudger* GetJudger() const { return m_judger; };
    void SetJudger(IJudger* judger) { m_judger = judger; }
    void Show(const Cards& pub,const std::map<IPlayer*,const Cards*>&) const;
    const int GetSmallBlind() const { return 10; };
    const int GetBigBlind() const { return GetBigBlind()*2; };
};
#endif
