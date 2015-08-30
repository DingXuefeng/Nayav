/***********************************
 * Class: CardTool
 *
 * Class for CardTool
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef CardTool_H
#define CardTool_H
#include "IDeskAdmin.h"
#include "Card.h"
#include "stdio.h"
#include <iostream>
#include <deque>
#include <string>
class CardTool {
  public:
    static const char* GetNumberName(int number);
    static const char* GetName(Card card);
    static const char* GetRoundName(const int round);
    static const std::string ToType(int rank);
    static const int Rank(const Cards &cards);
  private:
    static const int IsFlushStraight(const Cards &cards, CardMasks& mask);
    static const int IsFlush(const Cards &cards, CardMasks& mask);
    static const int IsStraight(const Cards &cards, CardMasks& mask);
    static const int IsFour(const Cards &cards, CardMasks& mask);
    static const int IsThree(const Cards &cards, CardMasks& mask);
    static const int IsPair(const Cards &cards, CardMasks& mask);

  private:
    static std::deque<char> unicode_to_utf8(int charcode); 
};
#endif
