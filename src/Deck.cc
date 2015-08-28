#include "Deck.h"
bool Deck::m_card_pool[] = {false};
bool Deck::m_initialized = false;

#include <stdlib.h>
#include <sys/time.h>
void Deck::Initialize() {
  struct timeval tp;
  gettimeofday(&tp,NULL);
  srand(tp.tv_usec);
  m_initialized = true;
}

#include <cstring>
void Deck::Flush() {
  memset(m_card_pool,false,N_Decks);
}

int Deck::GetRandom() {
  int result;
  do {
    result = (rand() % N_Decks);
  }while(m_card_pool[result]);
  m_card_pool[result] = true;
  return result;
}
