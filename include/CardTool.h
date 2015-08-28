/***********************************
 * Class: CardTool
 *
 * Class for CardTool
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef CardTool_H
#define CardTool_H
#include "Card.h"
#include "stdio.h"
#include <iostream>
#include <deque>
class CardTool {
  public:
    static const char* GetName(Card card);
  public:
    static bool IsPair(Cards &cards, const CardMasks& mask);
    static bool IsFlush(Cards &cards, const CardMasks& mask);
    static bool IsStraight(Cards &cards, const CardMasks& mask);

  private:
    static std::deque<char> unicode_to_utf8(int charcode); 
};
#endif
