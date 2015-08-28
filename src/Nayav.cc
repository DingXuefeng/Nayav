#include "Nayav.h"
Nayav* Nayav::f_Nayav = NULL;
Nayav* Nayav::Me() {
  if(!f_Nayav)
    f_Nayav = new Nayav;
  return f_Nayav;
}

#include "Player.h"
IPlayer::Action Nayav::GetAction() const {
  return call;
}
