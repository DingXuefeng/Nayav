#include <iostream>
#include "DeskAdmin.h"
using namespace std;
#include "Deck.h"
void DeskAdmin::StartNewDesk() {
  Deck::Initialize();
  int m_pos_D = 0;
  int a=0;
  while(true) {
    NewRounds();
    if(m_players->size()<2) break;
    m_pos_D = (m_pos_D+1)%m_players->size();
    a++;
    if(a==3) break;
  }
}

#include "CardTool.h"
#include "IJudger.h"
void DeskAdmin::NewRounds() {
  cout<<"New rounds. "<<endl;
  Deck::Flush();
  Players *on_desk = new Players(m_players->begin(),m_players->end());
  Cards pub_cards;
  std::map<IPlayer*,const Cards*> inhands;
  for(int round = pre_flop; round<=river; ++round) {
    switch(round) {
      case pre_flop:
	for(Players::iterator on_deskIt = on_desk->begin();
	    on_deskIt != on_desk->end(); on_deskIt++) {
	  printf("Player [%s] \t",(*on_deskIt)->GetName());
	  Cards * cards = new Cards;
	  cards->push_back(Deck::GetRandom());
	  cards->push_back(Deck::GetRandom());
	  inhands[*on_deskIt] = const_cast<const Cards*>(cards);
	  for(Cards::iterator cardsIt = cards->begin();
	      cardsIt != cards->end(); cardsIt++) {
	      cout<<(CardTool::GetName(*cardsIt))<<" ";
	  }
	  cout<<"\t\t";
	}
	cout<<"\t\t\tpre_flop"<<endl;
	break;
      case flop:
	cout<<"\t\t";
	for(int i = 0;i<3;i++)
	  pub_cards.push_back(Deck::GetRandom());
	for(int j = 0;j<2;j++) {
	  for(int i = 0;i<3;i++) {
	    cout<<(CardTool::GetName(pub_cards[i]))<<" ";
	  }
	  cout<<"\t\t\t\t";
	}
	cout<<"flop"<<endl;
	break;
      case turn:
	pub_cards.push_back(Deck::GetRandom());
	cout<<"\t\t";
	cout<<(CardTool::GetName(pub_cards[3]))<<" ";
	cout<<"\t\t\t\t\t";
	cout<<(CardTool::GetName(pub_cards[3]))<<" ";
	cout<<"\t\t\t\t\t";
	cout<<"turn"<<endl;
	break;
      case river:
	pub_cards.push_back(Deck::GetRandom());
	cout<<"\t\t";
	cout<<(CardTool::GetName(pub_cards[4]))<<" ";
	cout<<"\t\t\t\t\t";
	cout<<(CardTool::GetName(pub_cards[4]))<<" ";
	cout<<"\t\t\t\t\t";
	cout<<"river"<<endl;
	break;
      default:
	cout<<"Error"<<endl;
	break;
    }
  }
  IJudger* judger = GetJudger();
  IPlayer* winner = judger->Judge(pub_cards,inhands);
  printf("Winner is : [%s]\n",winner->GetName());
}

