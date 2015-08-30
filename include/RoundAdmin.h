/***********************************
 * Class: RoundAdmin
 *
 * Class for RoundAdmin
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef RoundAdmin_H
#define RoundAdmin_H
class IDeskAdmin;
#include "IPlayer.h"
//#include "Messenger.h"
class RoundAdmin {
  public:
    RoundAdmin(IDeskAdmin *deskAdmin);
    void AddPlayers(const Players &players);
    void SetDPlayer(IPlayer *D_player);
    void Initialize();
    void InitializeSingleRound();
    void Raise(IPlayer* raiser, const int raise);
    //////
    void BlindAction();
    void Loop();
    //////////////
  private:
    Players::iterator m_currentPlayer;
    Players::iterator m_roundsFirstPlayer;
    IPlayer *m_actionPlayer;
    IPlayer *m_smallBlind;
    IPlayer *m_bigBlind;
    IPlayer *m_stopPlayer;
    int m_round;
    int m_RoundBet;
    int m_pool;
  public:
    Players::iterator &GetCurrentPlayer() { return m_currentPlayer; }
    Players::iterator& GetroundsFirstPlayer() { return m_roundsFirstPlayer; }
    IPlayer *& GetActionPlayer() { return m_actionPlayer; }
    const IPlayer * GetActionPlayer() const { return m_actionPlayer; }
    IPlayer *& GetsmallBlind() { return m_smallBlind; }
    const IPlayer * GetsmallBlind() const { return m_smallBlind; }
    IPlayer *& GetbigBlind() { return m_bigBlind; }
    const IPlayer * GetbigBlind() const { return m_bigBlind; }
    IPlayer *& GetstopPlayer() { return m_stopPlayer; }
    const IPlayer * GetstopPlayer() const { return m_stopPlayer; }
    void AddBet(const int bet) { Getpool() += bet; }
    const int GetRoundBet() const { return m_RoundBet; }
    int& Getround() { return m_round; }
    const int Getround() const { return m_round; }
    int& GetRoundBet() { return m_RoundBet; }
    const int Getpool() const { return m_pool; }
    int& Getpool() { return m_pool; }
    void RecordStatus();
    void ShowStatus();
    Players & GetonDesk() { return m_onDesk; }
    const Players & GetonDesk() const { return m_onDesk; }
    void Next_OnDesk() { 
      ++GetCurrentPlayer();
      if(GetCurrentPlayer() == GetonDesk().end())
	GetCurrentPlayer() = GetonDesk().begin();
    };
    void PlayerAction();
    const bool IsBlind() const;
    const int GetBlind() const { return 10; };
    const IPlayer *GetD_player() const { return m_D_player; };
    IPlayer *&GetD_player() { return m_D_player; }

  private:
    void CurrentPlayerMoveToSmallBlind();
    IDeskAdmin *m_deskAdmin;
    IPlayer *m_D_player;
    Players m_onDesk;
    void InitializeEachPlayer();
    //Messenger m_messenger;
    //const Messenger GetMessenger() const { return m_messenger; }
    //Messenger &GetMessenger() { return m_messenger; }
    int m_tmp_RoundBet;
    int m_tmp_money;
    int m_tmp_bet;
    int m_tmp_pool;
};
#endif
