#include <iostream>
#include "DeskAdmin.h"
using namespace std;
#include "Deck.h"

void DeskAdmin::Raise(IPlayer* raiser, const int raise) { 
  GetRoundAdmin()->Raise(raiser,raise);
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
  GetRoundAdmin()->InitializeSingleRound();
}

void DeskAdmin::Loop() {
  GetRoundAdmin()->Loop();
}

void DeskAdmin::SendCards() {
  GetJudger()->SendCards();
}


void DeskAdmin::SendInhand() {
  for(Players::iterator on_deskIt = GetonDesk().begin();
      on_deskIt != GetonDesk().end(); on_deskIt++) {
    (*on_deskIt)->Initialize();
    Cards * cards = new Cards;
    cards->push_back(Deck::GetRandom());
    cards->push_back(Deck::GetRandom());
    Getinhands()[*on_deskIt] = const_cast<const Cards*>(cards);
  }
}

void DeskAdmin::FirstRoundLoop() {
  SendCards();
  SendInhand();
  Loop();
}

void DeskAdmin::RoundLoop(const int num_pub) {
  SendCards();
  for(int i = 0;i<num_pub;i++)
    GetpubCards().push_back(Deck::GetRandom());
  Loop();
}

#include "IJudger.h"
#include <list>
#include "RoundAdmin.h"
void DeskAdmin::NewRounds() {
  cout<<"=============================New rounds.==========================="<<endl;
  m_roundAdmin = new RoundAdmin(this);
  m_roundAdmin->AddPlayers(*m_players);
  m_roundAdmin->GetD_player() = (*m_D_player);
  m_roundAdmin->Initialize();

  Deck::Flush(); // initialize deck
  GetpubCards().clear(); // initialize pub cards
  Getinhands().clear(); // initialize in hand cards

  // start 4 rounds
  FirstRoundLoop(); // pre-flop round
  RoundLoop(3); // flop round
  RoundLoop(); // turn round
  RoundLoop(); // rive round

  // show cards
  IJudger* judger = GetJudger();
  judger->Judge(GetpubCards(),Getinhands());

  for(Players::const_iterator winnersIt = GetJudger()->GetWinners().begin();
      winnersIt != GetJudger()->GetWinners().end(); ++winnersIt)
    (*winnersIt)->Win(Getpool()/(GetJudger()->GetWinners().size()));

  Show();
}

void DeskAdmin::Show() const {
  GetJudger()->Show();
}
