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

#include "Messenger.h"
#include "CardTool.h"
#include <algorithm>
void DeskAdmin::NotifyUserStatus() const {
  for(Players::const_iterator onDeskIt = GetonDesk().begin();
      onDeskIt != GetonDesk().end(); ++onDeskIt) {
    char buff[255];
    int rank; {
      Cards* fullInhands = new Cards(
	  Getinhands().at(*onDeskIt)->size()+
	  GetpubCards().size());
      std::copy(Getinhands().at(*onDeskIt)->begin(),
	  Getinhands().at(*onDeskIt)->end(),
	  fullInhands->begin());
      std::copy(GetpubCards().begin(),GetpubCards().end(),fullInhands->begin()+2);

      CardTool::Sort(*fullInhands);
      rank = CardTool::Rank(*fullInhands);

      char buff[255];
      for(size_t i = 0;i<fullInhands->size();i++) {
	Cards::const_iterator cardsIt = 
	  std::find(Getinhands().at(*onDeskIt)->begin(),
	      Getinhands().at(*onDeskIt)->end(),fullInhands->at(i));
	if(cardsIt != Getinhands().at(*onDeskIt)->end())
	  sprintf(buff+i*8,"<%3s> ",CardTool::GetName(fullInhands->at(i)));
	else
	  sprintf(buff+i*8,"[%3s] ",CardTool::GetName(fullInhands->at(i)));
      }
      Messenger::Get()->Notify(*onDeskIt,buff);
      delete fullInhands;
    }
    sprintf(buff,"Money $[%4d] Bet[%4d] RoundBet[%4d] pool[%4d] inHand[%d](%s)",
	(*onDeskIt)->GetMoney(),
	(*onDeskIt)->GetBet(),
	GetRoundBet(),Getpool(),
	rank,
	CardTool::ToType(rank).c_str());
    Messenger::Get()->Notify(*onDeskIt,buff);

  }
}

#include <chrono>
#include <thread>
void DeskAdmin::RoundLoop() {
  GetJudger()->SendCards();
  NotifyUserStatus();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
  GetJudger()->Initialize();

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
