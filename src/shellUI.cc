#include "shellUI.h"
shellUI* shellUI::f_shellUI = NULL;

void shellUI::show(std::ostream &os, const char* message) {
  os<<message<<std::endl;
}

UI* shellUI::Get() {
  if(!f_shellUI) f_shellUI = new shellUI;
  return f_shellUI;
}
