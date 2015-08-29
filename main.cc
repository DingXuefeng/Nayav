#include "Users.h"
#include "Nayav.h"
#include "Eimer.h"
int main() {
  IDeskAdmin* eimer = Eimer::Me();
  Users::Loggin("dingxf","passwd")->JoinDesk(eimer);
  Nayav::New()->JoinDesk(eimer);
  Nayav::New()->JoinDesk(eimer);
  Nayav::New()->JoinDesk(eimer);
  Nayav::New()->JoinDesk(eimer);
  eimer->StartNewDesk();
  return 0;
}
