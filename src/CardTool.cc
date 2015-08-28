#include "CardTool.h"
#include <stdexcept>
bool CardTool::IsPair(Cards &cards,const CardMasks& mask) {
  if(cards.size()!=5)
    throw std::runtime_error("Is pair only accepts 2 cards.");
  return true;
}
bool CardTool::IsFlush(Cards &cards,const CardMasks& mask) {
  return true;
}
bool CardTool::IsStraight(Cards &cards,const CardMasks& mask) {
  return true;
}
const char* CardTool::GetName(Card card) {
  const int color = card%4; 
  std::deque<char> name;
  switch(color) {
    case 0:
      name = unicode_to_utf8(0x2660);
      break;
    case 1:
      name = unicode_to_utf8(0x2665);
      break;
    case 2:
      name = unicode_to_utf8(0x2666);
      break;
    case 3:
      name = unicode_to_utf8(0x2663);
      break;
    default:
      break;
  }
  char* result = new char[name.size()+3];
  std::copy(name.begin(),name.end(),result);
  const int number = card/4; // 0-12, 2,3,4,5,6,7,8,9,10,J,Q,K,A
  result[name.size()+1]='\0';
  switch(number) {
    case 0: // 1
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
    case 8:
      result[name.size()] = '1'+number;
      break;
    case 9: // 10
      result[name.size()] = '1';
      result[name.size()+1] = '0';
      result[name.size()+2]='\0';
      break;
    case 10:
    case 11:
    case 12:
      result[name.size()] = 'J'+number-10;
      break;
    case 13:
      result[name.size()] = 'A';
    default:
      break;
  }
  return result;
}
std::deque<char> CardTool::unicode_to_utf8(int charcode) {
  std::deque<char> d;
  if (charcode < 128)
  {
    d.push_back(charcode);
  }
  else
  {
    int first_bits = 6; 
    const int other_bits = 6;
    int first_val = 0xC0;
    int t = 0;
    while (charcode >= (1 << first_bits))
    {
      {
	t = 128 | (charcode & ((1 << other_bits)-1));
	charcode >>= other_bits;
	first_val |= 1 << (first_bits);
	first_bits--;
      }
      d.push_front(t);
    }
    t = first_val | charcode;
    d.push_front(t);
  }
  return d;
}
