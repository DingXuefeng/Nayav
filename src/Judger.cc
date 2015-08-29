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
  int rank_first = CardTool::Rank(*first);
  int rank_second = CardTool::Rank(*second);
  printf("Player [%10s]: %20s\n",
      inhands.begin()->first->GetName(),
      CardTool::ToType(rank_first).c_str());
  printf("Player [%10s]: %20s\n",
      (++inhands.begin())->first->GetName(),
      CardTool::ToType(rank_second).c_str());
  if(rank_first>rank_second)
    return inhands.begin()->first;
  else if(rank_second>rank_first)
    return (++inhands.begin())->first;
  else
    return NULL;
}
