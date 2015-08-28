/***********************************
 * Class: Deck
 *
 * Class for Deck
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Deck_H
#define Deck_H
#define N_Decks 52
class Deck {
  public:
    static void Initialize();
    static void Flush();
    static int GetRandom();
  private:
    static bool m_initialized;
    static bool m_card_pool[N_Decks];
};
#endif
