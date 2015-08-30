/***********************************
 * Class: Messenger
 *
 * Class for Messenger
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Messenger_H
#define Messenger_H
#include "IPlayer.h"
class Messenger {
  public:
    static Messenger* Get();
    static void Add(IPlayer* player) { Get()->m_players.push_back(player); };
    void Notify(IPlayer* player,const char* message);
    void Notify(const char* message);
  private:
    Players m_players;
    static Messenger* f_messenger;
};
#endif
