#include <iostream>
#include "DeskAdmin.h"
using namespace std;
#include "Deck.h"
void DeskAdmin::Raise(IPlayer* raiser, const int raise) { 
  m_raiser = raiser; m_roundBet += raise; 
}

void DeskAdmin::StartNewDesk() {
  Deck::Initialize();
  m_D_player = m_players->begin();
  int a=0;
  while(true) {
    // show round info
    cout<<" Players: ";
    int i = 0;
    for(Players::const_iterator m_playersIt = m_players->begin();
	m_playersIt != m_players->end(); ++m_playersIt, ++i) {
      cout<<" [";
      if(m_D_player == m_playersIt)
	cout<<"D";
      else
	cout<<i;
      cout<<"]"<<(*m_playersIt)->GetName();
    }
    cout<<endl;

    NewRounds();

    if(m_players->size()<2) break;
    ++m_D_player;
    if(m_D_player==m_players->end()) m_D_player = m_players->begin();
    a++;
    if(a==3) break;
  }
}

#include "CardTool.h"
void DeskAdmin::RoundInitialize() {
  m_roundBet = 0;
  m_raiser = NULL;
  GetCurrentPlayer() = m_roundsFirstPlayer;
  for(Players::iterator on_deskIt = m_onDesk->begin();
      on_deskIt != m_onDesk->end(); on_deskIt++)
    (*on_deskIt)->Initialize();
  cout<<"--------------------------New round.: <"<<CardTool::GetRoundName(m_round)<<
    ">-------------------------"<<endl;
}

void DeskAdmin::Loop() {
  CheckLoop();
  if(m_raiser) RaiseLoop();
  ++m_round;
  cout<<"---------------------------------End-------------------------------"<<endl;
}

void DeskAdmin::RoundLoop(const int num_pub) {
  for(int i = 0;i<num_pub;i++)
    m_pubCards.push_back(Deck::GetRandom());
  RoundInitialize();
  Loop();
}

void DeskAdmin::SendInhand() {
  for(Players::iterator on_deskIt = m_onDesk->begin();
      on_deskIt != m_onDesk->end(); on_deskIt++) {
    (*on_deskIt)->Initialize();
    Cards * cards = new Cards;
    cards->push_back(Deck::GetRandom());
    cards->push_back(Deck::GetRandom());
    m_inhands[*on_deskIt] = const_cast<const Cards*>(cards);
  }
}

void DeskAdmin::BlindAction() {
  PlayerAction();
  PlayerAction();
}

void DeskAdmin::FirstRoundLoop() {
  SendInhand();
  RoundInitialize();
  BlindAction();
  Loop();
}

#include "IJudger.h"
#include <list>
#include "RoundAdmin.h"
void DeskAdmin::NewRounds() {
  cout<<"=============================New rounds.==========================="<<endl;
  Deck::Flush(); // initialize deck
  m_pubCards.clear(); // initialize pub cards
  m_inhands.clear(); // initialize in hand cards
  m_pool = 0; // pool to zero
  m_roundAdmin = new RoundAdmin(this);
  m_roundAdmin->AddPlayers(*m_players);
  m_roundAdmin->SetDPlayer(*m_D_player);
  m_roundAdmin->Initialize();
  // initialize player on desk
  m_onDesk = new Players;
  Players::iterator on_deskIt = m_onDesk->begin();
  Players::const_iterator playersIt = m_players->begin();
  for(;playersIt != m_players->end(); ++playersIt) {
    m_onDesk->push_back((*playersIt)->Clone());
    ++on_deskIt; (*on_deskIt)->Initialize();
    if(playersIt == m_D_player) GetCurrentPlayer() = on_deskIt;
  }

  Next_OnDesk();
  m_roundsFirstPlayer = GetCurrentPlayer();
  m_smallBlind = *GetCurrentPlayer();
  Next_OnDesk();
  m_bigBlind = *GetCurrentPlayer();
  //cout<<" small: "<<m_smallBlind->GetName()<<" big: "<<m_bigBlind->GetName()<<endl;

  m_round = pre_flop; // initialize m_round

  // start 4 rounds
  FirstRoundLoop(); // pre-flop round
  RoundLoop(3); // flop round
  RoundLoop(); // turn round
  RoundLoop(); // rive round

  // show cards
  IJudger* judger = GetJudger();
  judger->Judge(m_pubCards,m_inhands);

  for(Players::const_iterator winnersIt = GetJudger()->GetWinners().begin();
      winnersIt != GetJudger()->GetWinners().end(); ++winnersIt)
    (*winnersIt)->Win(m_pool/(GetJudger()->GetWinners().size()));

  Show(m_pubCards,m_inhands);
}

void DeskAdmin::CheckLoop() {
  m_firstPlayer = *GetCurrentPlayer();
  do {
    PlayerAction();
  } while((*GetCurrentPlayer()!=m_firstPlayer)&&!m_raiser);
}

void DeskAdmin::RaiseLoop() {
  do {
    PlayerAction();
  } while(*GetCurrentPlayer()!=m_raiser);
}

void DeskAdmin::RecordStatus() {
  GetActionPlayer() = *GetCurrentPlayer(); m_tmp_roundBet = GetRoundBet();
  m_tmp_money = GetActionPlayer()->GetMoney();
  m_tmp_bet = GetActionPlayer()->GetBet();
  m_tmp_pool = m_pool;
}

#include <chrono>
#include <thread>
void DeskAdmin::ShowStatus() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  printf("Player [%8s] $ (%4d) => (%4d), Bet $ (%4d) => (%4d) \
      Round Bet $ (%4d) => (%4d) Bet Pool (%4d) => (%4d)\n",
      GetActionPlayer()->GetName(),
      m_tmp_money,GetActionPlayer()->GetMoney(),
      m_tmp_bet,GetActionPlayer()->GetBet(),
      m_tmp_roundBet,GetRoundBet(),
      m_tmp_pool,m_pool);
}

const bool DeskAdmin::IsBlind() const {
  return ((GetActionPlayer()==m_smallBlind)||(GetActionPlayer()==m_bigBlind));
}

void DeskAdmin::PlayerAction() {
  RecordStatus();
  if(IsBlind()) {
    GetActionPlayer()->Raise(GetBlind());
    if(GetActionPlayer()==m_smallBlind) m_smallBlind = NULL;
    if(GetActionPlayer()==m_bigBlind) m_bigBlind = NULL;
    m_raiser = NULL;
    cout<<" Bl Rs ";
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
	  if(m_firstPlayer == GetActionPlayer())
	    m_firstPlayer = *validPlayer;
	  if(m_raiser == GetActionPlayer())
	    m_raiser = *validPlayer;
	  // pointer move
	  Players::iterator quiter = GetCurrentPlayer();
	  --GetCurrentPlayer();
	  if(!*GetCurrentPlayer())
	    --GetCurrentPlayer();
	  // remove from desk
	  m_onDesk->erase(quiter); 
	}
	cout<<" Fold  ";
	break;
      case IPlayer::call:
	GetActionPlayer()->Call();
	cout<<" Call  ";
	break;
      case IPlayer::raise:
	GetActionPlayer()->Raise(GetActionPlayer()->GetRaisedMoney());
	cout<<" Raise ";
	break;
      default:
	break;
    }
  }
  ShowStatus();
  Next_OnDesk();
}

void DeskAdmin::Show(const Cards& m_pubCards, 
    const std::map<IPlayer*,const Cards*> &m_inhands) const {
  cout<<endl;
  for(Inhands::const_iterator m_inhandsIt = m_inhands.begin();
      m_inhandsIt != m_inhands.end(); ++m_inhandsIt ){
    printf("Player [%8ss] [-->",m_inhandsIt->first->GetName());
    for(Cards::const_iterator cardsIt = m_inhandsIt->second->begin();
	cardsIt != m_inhandsIt->second->end(); cardsIt++) {
      cout<<"["<<CardTool::GetName(*cardsIt)<<"] ";
    }
    cout<<" <--] pub --> ( ";
    for(size_t i = 0;i<m_pubCards.size();i++) {
      cout<<"["<<CardTool::GetName(m_pubCards[i])<<"] ";
    }
    if(GetJudger()->GetWinnerRank() == GetJudger()->GetMarks().at(m_inhandsIt->first))
      cout<<") [Win! ] : <";
    else
      cout<<") [Loose] : <";
    cout<<CardTool::ToType(GetJudger()->GetMarks().at(m_inhandsIt->first))<<">"<<endl;
  }
}
