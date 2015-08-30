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
