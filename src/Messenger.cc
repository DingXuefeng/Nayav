#include "Messenger.h"
Messenger* Messenger::f_messenger = NULL;

Messenger* Messenger::Get() {
  if(!f_messenger)
    f_messenger = new Messenger;
  return f_messenger;
}

void Messenger::Notify(const char* message) {
  for(Players::const_iterator playersIt = m_players.begin();
      playersIt != m_players.end(); ++playersIt)
    Notify(*playersIt,message);
}

#include "UI.h"
void Messenger::Notify(IPlayer *player, const char* message) {
  player->GetUI()->show(player->GetOs(),message);
}
