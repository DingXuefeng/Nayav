#include "Eimer.h"
Eimer* Eimer::f_Eimer = NULL;
Eimer* Eimer::Me() {
  if(!f_Eimer)
    f_Eimer = new Eimer;
  return f_Eimer;
}
