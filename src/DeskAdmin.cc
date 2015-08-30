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

void DeskAdmin::RoundLoop() {
  GetJudger()->SendCards();
  GetRoundAdmin()->Loop();
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

  // start 4 rounds
  RoundLoop(); // pre flop round
  RoundLoop(); // flop round
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
