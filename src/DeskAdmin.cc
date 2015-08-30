#include <iostream>
#include "DeskAdmin.h"
using namespace std;
#include "Deck.h"
void DeskAdmin::Raise(IPlayer* raiser, const int raise) { 
  m_raiser = *m_currentPlayer; m_roundBet += raise; 
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
	m_playersIt != m_players->end(); ++m_playersIt) {
      cout<<" ["<<++i<<"]"<<(*m_playersIt)->GetName();
      if(m_D_player == m_playersIt)
	cout<<"(D Player)";
    }
    cout<<endl;
    //

    NewRounds();
    if(m_players->size()<2) break;
    ++m_D_player;
    if(m_D_player==m_players->end()) m_D_player = m_players->begin();
    a++;
    if(a==3) break;
  }
}

void DeskAdmin::RoundInitialize() {
  m_roundBet = 0;
  m_raiser = NULL;
  m_currentPlayer = m_roundsFirstPlayer;
  cout<<"-----------------------------New round.----------------------------"<<endl;
}

void DeskAdmin::RoundLoop() {
  CheckLoop();
  if(m_raiser) RaiseLoop();
  cout<<"---------------------------------End-------------------------------"<<endl;
}

#include "CardTool.h"
#include "IJudger.h"
#include <list>
void DeskAdmin::NewRounds() {
  cout<<"=============================New rounds.==========================="<<endl;
  Deck::Flush(); // initialize deck
  // initialize m_roundesk
  m_onDesk = new Players;
  for(Players::const_iterator playersIt = m_players->begin();
      playersIt != m_players->end(); ++playersIt)
    m_onDesk->push_back(*playersIt);

  // initialize m_roundsFirstPlayer
  for(m_currentPlayer = m_onDesk->begin();
      *m_currentPlayer != *m_D_player; ++m_currentPlayer) 
    ;
  Next_OnDesk();
  m_roundsFirstPlayer = m_currentPlayer;

  // prepare pub cards and in hand cards
  Cards pub_cards;
  std::map<IPlayer*,const Cards*> inhands;
  
  // start 4 rounds
  for(int round = pre_flop; round<=river; ++round) {
    switch(round) {
      case pre_flop:
	for(Players::iterator on_deskIt = m_onDesk->begin();
	    on_deskIt != m_onDesk->end(); on_deskIt++) {
	  (*on_deskIt)->Initialize();
	  Cards * cards = new Cards;
	  cards->push_back(Deck::GetRandom());
	  cards->push_back(Deck::GetRandom());
	  inhands[*on_deskIt] = const_cast<const Cards*>(cards);
	}

	RoundInitialize();
	RecordStatus(); (*m_currentPlayer)->Raise(GetBlind()); 
	cout<<" Bet   "; ShowStatus(); 
	Next_OnDesk(); RecordStatus(); (*m_currentPlayer)->Raise(GetBlind());
	cout<<" Raise "; ShowStatus();
	m_raiser = NULL;
	RoundLoop();
	break;
      case flop:
	for(int i = 0;i<3;i++)
	  pub_cards.push_back(Deck::GetRandom());
	RoundInitialize();
	RoundLoop();
	break;
      case turn:
	pub_cards.push_back(Deck::GetRandom());
	RoundInitialize();
	RoundLoop();
	break;
      case river:
	pub_cards.push_back(Deck::GetRandom());
	RoundInitialize();
	RoundLoop();
	break;
      default:
	cout<<"error"<<endl;
	break;
    }
  }

  // show cards
  Show(pub_cards,inhands);

  // get result
  IJudger* judger = GetJudger();
  IPlayer* winner = judger->Judge(pub_cards,inhands);
  if(winner)
    printf("winner is : [%s]\n",winner->GetName());
  else
    printf("fair!\n");
}

void DeskAdmin::CheckLoop() {
  m_firstPlayer = *m_currentPlayer;
  do {
    Next_OnDesk();
    PlayerAction();
  } while((*m_currentPlayer!=m_firstPlayer)&&!m_raiser);
}

void DeskAdmin::RaiseLoop() {
  Next_OnDesk();
  do {
    PlayerAction();
    Next_OnDesk();
  } while(*m_currentPlayer!=m_raiser);
}

void DeskAdmin::RecordStatus() {
  m_actionPlayer = *m_currentPlayer;
  m_tmp_roundBet = GetRoundBet();
  m_tmp_money = m_actionPlayer->GetMoney();
  m_tmp_bet = m_actionPlayer->GetBet();
}

void DeskAdmin::ShowStatus() {
  printf("Player [%8s] $ (%4d) => (%4d), Bet $ (%4d) => (%4d) \
Round Bet $ (%4d) => (%4d)\n",m_actionPlayer->GetName(),
  m_tmp_money,m_actionPlayer->GetMoney(),
  m_tmp_bet,m_actionPlayer->GetBet(),
  m_tmp_roundBet,GetRoundBet());
}

void DeskAdmin::PlayerAction() {
  RecordStatus();
  IPlayer::Action action = m_actionPlayer->GetAction();
  switch(action) {
    case IPlayer::fold:
      {
	// record raiser & first
	Players::const_iterator validPlayer = m_currentPlayer;
	++validPlayer;
	if(!*validPlayer)
	  ++validPlayer;
	if(m_firstPlayer == m_actionPlayer)
	  m_firstPlayer = *validPlayer;
	if(m_raiser == m_actionPlayer)
	  m_raiser = *validPlayer;
	// pointer move
	Players::iterator quiter = m_currentPlayer;
	--m_currentPlayer;
	if(!*m_currentPlayer)
	  --m_currentPlayer;
	// remove from desk
	m_onDesk->erase(quiter); 
      }
      cout<<" Fold  ";
      break;
    case IPlayer::call:
      m_actionPlayer->Call();
      cout<<" Call  ";
      break;
    case IPlayer::raise:
      m_actionPlayer->Raise(m_actionPlayer->GetRaisedMoney());
      cout<<" Raise ";
      break;
    default:
      break;
  }
  ShowStatus();
}

void DeskAdmin::Show(const Cards& pub_cards, 
    const std::map<IPlayer*,const Cards*> &inhands) const {
  cout<<endl;
  for(Inhands::const_iterator inhandsIt = inhands.begin();
      inhandsIt != inhands.end(); ++inhandsIt ){
    printf("Player [%8ss] [-->",inhandsIt->first->GetName());
    for(Cards::const_iterator cardsIt = inhandsIt->second->begin();
	cardsIt != inhandsIt->second->end(); cardsIt++) {
      cout<<"["<<CardTool::GetName(*cardsIt)<<"] ";
    }
    cout<<" <--] pub --> ( ";
    for(int i = 0;i<3;i++) {
      cout<<"["<<CardTool::GetName(pub_cards[i])<<"] ";
    }
    cout<<" )"<<endl;
  }
}
