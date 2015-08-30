/***********************************
 * Class: shellUI
 *
 * Class for shellUI
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef shellUI_H
#define shellUI_H
#include "UI.h"
class shellUI : public UI {
  public:
    void show(std::ostream &os, const char* message);
    static UI* Get();
  private:
    static shellUI* f_shellUI;
};
#endif
