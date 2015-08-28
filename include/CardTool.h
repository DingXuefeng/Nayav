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
#include <string>
class CardTool {
  public:
    static const char* GetName(Card card);
    static const std::string ToType(int rank);
    static int Rank(const Cards &cards, const CardMasks& mask);
  private:
    static bool IsKingFlushStraight(const Cards &cards, CardMasks& mask);
    static bool IsFlushStraight(const Cards &cards, CardMasks& mask);
    static bool IsFullhouse(const Cards &cards, CardMasks& mask);
    static bool IsFlush(const Cards &cards, CardMasks& mask);
    static bool IsStraight(const Cards &cards, CardMasks& mask);
    static bool IsFour(const Cards &cards, CardMasks& mask);
    static bool IsThree(const Cards &cards, CardMasks& mask);
    static bool IsTwopair(const Cards &cards, CardMasks& mask);
    static bool IsPair(const Cards &cards, CardMasks& mask);

  private:
    static std::deque<char> unicode_to_utf8(int charcode); 
};
#endif
