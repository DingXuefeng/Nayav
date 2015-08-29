#include "Users.h"
#include "Nayav.h"
#include "Eimer.h"
int main() {
  IPlayer* dingxf = Users::Loggin("dingxf","passwd");
  IPlayer* nayav = Nayav::Me();

  IDeskAdmin* eimer = Eimer::Me();
  nayav->JoinDesk(eimer);
  dingxf->JoinDesk(eimer);
  eimer->StartNewDesk();
  return 0;
}
