#include "RoundAdmin.h"

RoundAdmin::RoundAdmin(IDeskAdmin *deskAdmin) : 
  m_deskAdmin(deskAdmin),m_D_player(NULL) {
};

void RoundAdmin::AddPlayers(const Players &players) {
  GetonDesk().clear();
  for(Players::const_iterator playersIt = players.begin();
      playersIt != players.end(); ++playersIt) {
    GetonDesk().push_back((*playersIt)->Clone());
  }
}

#include <stdexcept>
void RoundAdmin::CurrentPlayerMoveToSmallBlind() {
  if(!GetD_player())
    throw std::runtime_error("RoundAdmin::SetFirstPlayer: D player not set.");
  Players::iterator onDeskIt = GetonDesk().begin();
  while(*onDeskIt != GetD_player()) 
    ++onDeskIt;
  ++onDeskIt; if(onDeskIt == GetonDesk().end()) ++onDeskIt;
  GetCurrentPlayer() = onDeskIt;
}

void RoundAdmin::InitializeEachPlayer() {
  Players::const_iterator onDeskIt = GetonDesk().begin();
  for(;onDeskIt != GetonDesk().end(); ++onDeskIt)
    (*onDeskIt)->Initialize();
}

#include "IDeskAdmin.h"
void RoundAdmin::Initialize() {
  Getpool() = 0; // pool to zero
  CurrentPlayerMoveToSmallBlind();
  GetroundsFirstPlayer() = GetCurrentPlayer(); // set rounds first player
  GetsmallBlind() = *GetCurrentPlayer(); // set small blind
  Next_OnDesk(); GetbigBlind() = *GetCurrentPlayer(); // set big blind
  Getround() = IDeskAdmin::pre_flop; // initialize Getround()
}

#include "Messenger.h"
#include "CardTool.h"
void RoundAdmin::InitializeSingleRound() {
  GetRoundBet() = 0;
  InitializeEachPlayer();
  GetCurrentPlayer() = GetroundsFirstPlayer();
  for(Players::iterator on_deskIt = GetonDesk().begin();
      on_deskIt != GetonDesk().end(); on_deskIt++)
    (*on_deskIt)->Initialize();
  char message[255];
  sprintf(message,"------------------------\
--New round.: <%s>-------------------------",CardTool::GetRoundName(Getround()));
  Messenger::Get()->Notify(message);
}

void RoundAdmin::RecordStatus() {
  m_tmp_RoundBet = GetRoundBet();
  m_tmp_money = GetActionPlayer()->GetMoney();
  m_tmp_bet = GetActionPlayer()->GetBet();
  m_tmp_pool = Getpool();
}

#include <chrono>
#include <thread>
void RoundAdmin::ShowStatus() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  printf("Player [%8s] $ (%4d) => (%4d), Bet $ (%4d) => (%4d) \
      Round Bet $ (%4d) => (%4d) Bet Pool (%4d) => (%4d)\n",
      GetActionPlayer()->GetName(),
      m_tmp_money,GetActionPlayer()->GetMoney(),
      m_tmp_bet,GetActionPlayer()->GetBet(),
      m_tmp_RoundBet,GetRoundBet(),
      m_tmp_pool,Getpool());
}

const bool RoundAdmin::IsBlind() const {
  return ((GetActionPlayer()==GetsmallBlind())||(GetActionPlayer()==GetbigBlind()));
}

#include <string>
#include "CardTool.h"
void RoundAdmin::PlayerAction() {
  GetActionPlayer() = *GetCurrentPlayer(); 
  //RecordStatus();
  std::string action_str;
  if(IsBlind()) {
    GetActionPlayer()->Raise(GetBlind());
    char buff[255];
    sprintf(buff,"Blind <%4d>",GetBlind());
    action_str = buff;
    if(GetActionPlayer()==GetsmallBlind()) GetsmallBlind() = NULL;
    if(GetActionPlayer()==GetbigBlind()) GetbigBlind() = NULL;
  } else {
    IPlayer::Action action = GetActionPlayer()->GetAction();
    switch(action) {
      case IPlayer::fold:
	{
	  // record raiser & first
	  Players::const_iterator validPlayer = GetCurrentPlayer();
	  ++validPlayer;
	  if(!*validPlayer)
	    ++validPlayer;
	  if(GetstopPlayer() == GetActionPlayer())
	    GetstopPlayer() = *validPlayer;
	  // pointer move
	  Players::iterator quiter = GetCurrentPlayer();
	  --GetCurrentPlayer();
	  if(!*GetCurrentPlayer())
	    --GetCurrentPlayer();
	  // remove from desk
	  GetonDesk().erase(quiter); 
	}
	action_str = "Fold";
	break;
      case IPlayer::call:
	GetActionPlayer()->Call();
	action_str = "Call";
	break;
      case IPlayer::raise:
	{
	  int raisedMoney = GetActionPlayer()->GetRaisedMoney();
	  GetActionPlayer()->Raise(raisedMoney);
	  char buff[255];
	  sprintf(buff,"Raise by <%4d>",raisedMoney);
	  action_str = buff;
	}
	break;
      default:
	break;
    }
  }
  char message[255];
  sprintf(message,"Player [%8s] Action [%-15s]",
      GetActionPlayer()->GetName(),action_str.c_str());
  Messenger::Get()->Notify(message);
  //ShowStatus();
  Next_OnDesk();
}

void RoundAdmin::BlindAction() {
  PlayerAction();
  PlayerAction();
}

void RoundAdmin::Loop() {
  InitializeSingleRound();
  if(Getround() == IDeskAdmin::pre_flop)
    BlindAction();
  GetstopPlayer() = *GetCurrentPlayer();
  do {
    PlayerAction();
  } while(*GetCurrentPlayer()!=GetstopPlayer());
  ++Getround();
  Messenger::Get()->Notify("----------------------------\
-----End-------------------------------");
}

void RoundAdmin::Raise(IPlayer* raiser, const int raise) { 
  GetstopPlayer() = raiser;
  GetRoundBet() += raise; 
}
