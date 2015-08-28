#include <iostream>
#include "Judger.h"
using namespace std;
#include "Deck.h"
IPlayer* Judger::Judge(const Cards &pub,const std::map<IPlayer *,const Cards *>& inhands) {
  return inhands.begin()->first;
}
