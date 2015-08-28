#include "Users.h"
#include "Nayav.h"
#include "Eimer.h"
int main() {
  IPlayer* dingxf = Users::Loggin("dingxf","passwd");
  IPlayer* nayav = Nayav::Me();

  IDeskAdmin* eimer = Eimer::Me();
  eimer->Participate(nayav);
  eimer->Participate(dingxf);
  eimer->StartNewDesk();
  return 0;
}
