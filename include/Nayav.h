/***********************************
 * Class: Nayav
 *
 * Class for Nayav
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Nayav_H
#define Nayav_H
#include "Player.h"
#include "shellUI.h"
#include <fstream>
class Nayav : public Player{
  public:
    Action GetAction() const;
    const int GetRaisedMoney() const { return 10; }
    static IPlayer* New(const char* name = "\0");

  private:
    Nayav(const char* name = "Nayav") : Player(1000,false,0,name) {
      m_null.open("/dev/null");
    };
    static std::vector<Nayav*> f_Nayavs;
  private:
    UI *GetUI() { return shellUI::Get(); };
    std::ostream &GetOs() { return m_null; };
    std::ofstream m_null;
};
#endif
