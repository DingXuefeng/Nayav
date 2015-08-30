#include <iostream>
#include "Judger.h"
using namespace std;
#include "Deck.h"
#include "CardTool.h"
const Players& Judger::Judge(const Cards &pub,const Inhands& inhands) {
  // read data
  Inhands::const_iterator inhandsIt = inhands.begin(); 
  for(; inhandsIt != inhands.end(); ++inhandsIt) {
    Cards* fullInhands = new Cards(7);
    std::copy(pub.begin(),pub.end(),fullInhands->begin());
    std::copy(inhandsIt->second->begin(),inhandsIt->second->end(),fullInhands->begin()+5);
    m_fullInhands[inhandsIt->first] = fullInhands;
  }
  // give mark
  m_winnerRank = 0;
  inhandsIt = m_fullInhands.begin(); 
  for(; inhandsIt != m_fullInhands.end(); ++inhandsIt) {
    m_marks[inhandsIt->first] = CardTool::Rank(*(inhandsIt->second));
    if(m_marks[inhandsIt->first] >= m_winnerRank) {
      if(m_marks[inhandsIt->first] > m_winnerRank) {
	m_winner.clear();
	m_winnerRank = m_marks[inhandsIt->first];
      }
      m_winner.push_back(inhandsIt->first);
    }
  }
  return m_winner;
}

#include <stdexcept>
void Judger::SendCards() {
  switch(GetDeskAdmin()->Getround()) {
    case IDeskAdmin::pre_flop:
      Sendinhands(); break;
    case IDeskAdmin::flop:
      SendpubCards(3); break;
    case IDeskAdmin::turn:
    case IDeskAdmin::river:
      SendpubCards(1); break;
    default:
      throw std::runtime_error("Judge::SendpubCards(): Unknown round status.");
  }
}

void Judger::Sendinhands() {
  for(Players::const_iterator on_deskIt = GetonDesk().begin();
      on_deskIt != GetonDesk().end(); on_deskIt++) {
    Cards * cards = new Cards;
    cards->push_back(Deck::GetRandom());
    cards->push_back(Deck::GetRandom());
    Getinhands()[*on_deskIt] = const_cast<const Cards*>(cards);
  }
}

void Judger::SendpubCards(int num_pub) {
  /*
  for(int i = 0;i<num_pub;i++)
    GetpubCards().push_back(Deck::GetRandom());
    */
}

void Judger::Show() const {
  cout<<endl;
  for(Inhands::const_iterator inhandsIt = Getinhands().begin();
      inhandsIt != Getinhands().end(); ++inhandsIt ){
    printf("Player [%8ss] [-->",inhandsIt->first->GetName());
    for(Cards::const_iterator cardsIt = inhandsIt->second->begin();
	cardsIt != inhandsIt->second->end(); ++cardsIt) {
      cout<<"["<<CardTool::GetName(*cardsIt)<<"] ";
    }
    cout<<" <--] pub --> ( ";
    for(size_t i = 0;i<GetpubCards().size(); ++i) {
      cout<<"["<<CardTool::GetName(GetpubCards()[i])<<"] ";
    }
    if(GetWinnerRank() == GetMarks().at(inhandsIt->first))
      cout<<") [Win! ] : <";
    else
      cout<<") [Loose] : <";
    cout<<CardTool::ToType(GetMarks().at(inhandsIt->first))<<">"<<endl;
  }
}
