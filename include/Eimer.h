/***********************************
 * Class: Eimer
 *
 * Class for Eimer
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#include "DeskAdmin.h"
class Eimer : public DeskAdmin {
  public:
    static Eimer* Me();
  private:
    static Eimer* f_Eimer;
};
