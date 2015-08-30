/***********************************
 * Class: UI
 *
 * Class for UI
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef UI_H
#define UI_H
#include <iostream>
class UI {
  public:
    virtual void show(std::ostream &os, const char* message) = 0;
};
#endif
