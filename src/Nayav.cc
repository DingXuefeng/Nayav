#include "Nayav.h"
std::vector<Nayav*> Nayav::f_Nayavs;
#include <cstdio>
IPlayer* Nayav::New(const char* name) {
  if(name[0] == '\0') {
    name = new char[10];
    sprintf(const_cast<char*>(name),"Naya(%d)",int(f_Nayavs.size()+1));
  }
  Nayav* naya = new Nayav(name);
  f_Nayavs.push_back(naya);
  return naya;
}

#include "Player.h"
IPlayer::Action Nayav::GetAction() const {
  return call;
  if(GetDeskAdmin()->GetRoundBet()<50)
    return raise;
  else if(GetDeskAdmin()->GetRoundBet()>200)
    return fold;
  else
    return call;
}
