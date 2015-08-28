#include <iostream>
#include "Judger.h"
using namespace std;
#include "Deck.h"
#include "CardTool.h"
IPlayer* Judger::Judge(const Cards &pub,const std::map<IPlayer *,const Cards *>& inhands) {
  Cards *first(new Cards(7)),*second(new Cards(7));
  std::copy(pub.begin(),pub.end(),first->begin());
  std::copy(((inhands.begin())->second)->begin(),((inhands.begin())->second)->end(),first->begin()+5);
  std::copy(pub.begin(),pub.end(),second->begin());
  std::copy((++(inhands.begin()))->second->begin(),(++(inhands.begin()))->second->end(),second->begin()+5);
  CardMasks mask;
  mask.push_back(false);
  mask.push_back(false);
  mask.push_back(false);
  mask.push_back(false);
  mask.push_back(false);
  mask.push_back(false);
  mask.push_back(false);
  printf("Player [%10s]: %20s\n",
      inhands.begin()->first->GetName(),
      CardTool::ToType(CardTool::Rank(*first,mask)).c_str());
  printf("Player [%10s]: %20s\n",
      (++inhands.begin())->first->GetName(),
      CardTool::ToType(CardTool::Rank(*second,mask)).c_str());
  if(CardTool::Rank(*first,mask)>CardTool::Rank(*second,mask)) 
    return inhands.begin()->first;
  else
    return (++inhands.begin())->first;
}
