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

#include "CardTool.h"
#include "IJudger.h"
#include <list>
void DeskAdmin::NewRounds() {
  cout<<"=============================New rounds.==========================="<<endl;
  Deck::Flush();
  Players *on_desk = new Players(*m_players);
  m_onDesk = on_desk;
  Cards pub_cards;
  std::map<IPlayer*,const Cards*> inhands;
  m_currentPlayer = m_D_player;
  for(int round = pre_flop; round<=river; ++round) {
    switch(round) {
      case pre_flop:
	for(Players::iterator on_deskIt = on_desk->begin();
	    on_deskIt != on_desk->end(); on_deskIt++) {
	  (*on_deskIt)->Initialize();
	  printf("Player [%s] $[%4d]\t",
	      (*on_deskIt)->GetName(),(*on_deskIt)->GetMoney());
	  Cards * cards = new Cards;
	  cards->push_back(Deck::GetRandom());
	  cards->push_back(Deck::GetRandom());
	  inhands[*on_deskIt] = const_cast<const Cards*>(cards);
	  for(Cards::iterator cardsIt = cards->begin();
	      cardsIt != cards->end(); cardsIt++) {
	    cout<<(CardTool::GetName(*cardsIt))<<" ";
	    //	      printf("%2d ",*cardsIt);
	  }
	  cout<<"\t\t";
	}
	cout<<"\t\t\tpre_flop"<<endl;

	m_roundBet = 0;
	Next_OnDesk(); RecordStatus(); (*m_currentPlayer)->Raise(GetBlind());
	cout<<" Bet   "; ShowStatus(); 
	Next_OnDesk(); RecordStatus(); (*m_currentPlayer)->Raise(GetBlind());
	cout<<" Raise "; ShowStatus();
	m_raiser = NULL;
	CheckLoop();
	if(m_raiser) RaiseLoop();
	break;
      case flop:
	cout<<"\t\t";
	cout<<"\t";
	for(int i = 0;i<3;i++)
	  pub_cards.push_back(Deck::GetRandom());
	for(int j = 0;j<2;j++) {
	  for(int i = 0;i<3;i++) {
	    cout<<(CardTool::GetName(pub_cards[i]))<<" ";
	    //	    printf("%2d ",pub_cards[i]);
	  }
	  cout<<"\t";
	  cout<<"\t\t\t\t";
	}
	cout<<"flop"<<endl;
	break;
      case turn:
	pub_cards.push_back(Deck::GetRandom());
	cout<<"\t\t";
	cout<<"\t";
	cout<<(CardTool::GetName(pub_cards[3]))<<" ";
	//	printf("%2d ",pub_cards[3]);
	cout<<"\t";
	cout<<"\t\t\t\t\t";
	cout<<(CardTool::GetName(pub_cards[3]))<<" ";
	cout<<"\t\t\t\t\t";
	cout<<"\t";
	cout<<"turn"<<endl;
	break;
      case river:
	pub_cards.push_back(Deck::GetRandom());
	cout<<"\t\t";
	cout<<"\t";
	cout<<(CardTool::GetName(pub_cards[4]))<<" ";
	//	printf("%2d ",pub_cards[4]);
	cout<<"\t";
	cout<<"\t\t\t\t\t";
	cout<<(CardTool::GetName(pub_cards[4]))<<" ";
	cout<<"\t\t\t\t\t";
	cout<<"\t";
	cout<<"river"<<endl;
	break;
      default:
	cout<<"error"<<endl;
	break;
    }
  }
  Show(pub_cards,inhands);
  IJudger* judger = GetJudger();
  IPlayer* winner = judger->Judge(pub_cards,inhands);
  if(winner)
    printf("winner is : [%s]\n",winner->GetName());
  else
    printf("fair!\n");
}

void DeskAdmin::CheckLoop() {
  IPlayer* firstPlayer = *m_currentPlayer;
  do {
    Next_OnDesk();
    PlayerAction();
  } while((*m_currentPlayer!=firstPlayer)&&!m_raiser);
}

void DeskAdmin::RaiseLoop() {
  Next_OnDesk();
  do {
    PlayerAction();
    Next_OnDesk();
  } while(*m_currentPlayer!=m_raiser);
}

void DeskAdmin::RecordStatus() {
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
  m_actionPlayer = *m_currentPlayer;
  IPlayer::Action action = m_actionPlayer->GetAction();
  RecordStatus();
  switch(action) {
    case IPlayer::fold:
      {
	Players::iterator quiter = m_currentPlayer;
	--m_currentPlayer;
	if(!*m_currentPlayer)
	  --m_currentPlayer;
	m_onDesk->erase(quiter); 
      }
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
    printf("Player [%s] \t",inhandsIt->first->GetName());
    for(Cards::const_iterator cardsIt = inhandsIt->second->begin();
	cardsIt != inhandsIt->second->end(); cardsIt++) {
      cout<<((*cardsIt))<<" ";
    }
    cout<<"\t\t\t";
  }
  cout<<"\t\tpre_flop"<<endl;
  cout<<"\t\t";
  for(int j = 0;j<2;j++) {
    for(int i = 0;i<3;i++) {
      cout<<((pub_cards[i]))<<" ";
      //	    printf("%2d ",pub_cards[i]);
    }
    cout<<"\t\t\t\t";
  }
  cout<<"flop"<<endl;
  cout<<"\t\t";
  cout<<((pub_cards[3]))<<" ";
  //	printf("%2d ",pub_cards[3]);
  cout<<"\t\t\t\t\t";
  cout<<((pub_cards[3]))<<" ";
  cout<<"\t\t\t\t\t";
  cout<<"turn"<<endl;
  cout<<"\t\t";
  cout<<((pub_cards[4]))<<" ";
  //	printf("%2d ",pub_cards[4]);
  cout<<"\t\t\t\t\t";
  cout<<((pub_cards[4]))<<" ";
  cout<<"\t\t\t\t\t";
  cout<<"river"<<endl;
}
