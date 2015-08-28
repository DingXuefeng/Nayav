#include "CardTool.h"
#include <stdexcept>
enum {
  royal_straight_flush = 90000,
  straight_flush = 80000,
  four = 70000,
  full_house = 60000,
  flush = 50000,
  straight = 40000,
  three = 30000,
  two_pair = 20000,
  pair = 10000,
  none = 0
};
const std::string CardTool::ToType(int rank) {
  switch(rank) {
    case 0:
      return "none";
    case 10000:
      return "pair";
    case 20000:
      return "two_pair";
    case 30000:
      return "three";
    case 40000:
      return "straight";
    case 50000:
      return "flush";
    case 60000:
      return "full house";
    case 70000:
      return "four";
    case 80000:
      return "flush straight";
    case 90000:
      return "Royal flush straight";
    default:
      return "Unknown";
  }
}
int CardTool::Rank(const Cards &cards,const CardMasks& mask) {
  CardMasks _mask(mask.size());
  std::copy(mask.begin(),mask.end(),_mask.begin());
  Cards _cards(cards.size());
  std::copy(cards.begin(),cards.end(),_cards.begin());
  for(size_t i = 0;i<_cards.size()-1;i++)
    for(size_t j = i+1;j<_cards.size();j++)
      if(_cards[i]/4<_cards[j]/4) {
	Card tmp = _cards[i];
	_cards[i] = _cards[j];
	_cards[j] = tmp;
      }
  if(IsFlush(_cards,_mask))
    if(IsStraight(_cards,_mask))
      return straight_flush;
    else
      return flush;
  else {
    if(IsStraight(_cards,_mask))
      return straight;
    else {
      if(IsFour(_cards,_mask))
	return four;
      else {
	if(IsThree(_cards,_mask)) {
	  if(IsPair(_cards,_mask))
	    return full_house; // full house
	  else
	    return three; // three
	} else {
	  if(IsPair(_cards,_mask)) {
	    if(IsPair(_cards,_mask))
	      return two_pair;
	    else
	      return pair;
	  }
	}
	return none;
      }
    }
  }
}
//throw std::runtime_error("Is pair only accepts 2 cards.");
#include <iostream>
using std::cout;
using std::endl;
bool CardTool::IsPair(const Cards &cards,CardMasks& mask) {
  for(size_t i = 0;i<cards.size()-1;i++)
    if(!mask[i])
      for(size_t j = i+1;j<cards.size();j++)
	if(!mask[j])
	  if(cards[i]/4==cards[j]/4) {
	    mask[i] = true;
	    mask[j] = true;
	    return true;
	  }
  return false;
}

bool CardTool::IsThree(const Cards &cards,CardMasks& mask) {
  for(size_t i = 0;i<cards.size()-2;i++)
    if(!mask[i])
      for(size_t j = i+1;j<cards.size()-1;j++)
	if(!mask[j])
	  if(cards[i]/4==cards[j]/4)
	    for(size_t k = j+1;k<cards.size();k++)
	      if(!mask[k])
		if(cards[i]/4==cards[k]/4) {
		  mask[i] = true;
		  mask[j] = true;
		  mask[k] = true;
		  return true;
		}
  return false;
}

bool CardTool::IsFour(const Cards &cards,CardMasks& mask) {
  for(size_t i = 0;i<cards.size()-3;i++)
    if(!mask[i])
      for(size_t j = i+1;j<cards.size()-2;j++)
	if(!mask[j])
	  if(cards[i]/4==cards[j]/4)
	    for(size_t k = j+1;k<cards.size()-1;k++)
	      if(!mask[k])
		if(cards[i]/4==cards[k]/4)
		  for(size_t l = k+1;l<cards.size();l++)
		    if(!mask[l])
		      if(cards[i]/4==cards[l]/4)
			return true;
  return false;
}
bool CardTool::IsFlush(const Cards &cards, CardMasks& mask) {
  for(size_t i = 0;i<cards.size()-4;i++)
    if(!mask[i])
      for(size_t j = i+1;j<cards.size()-3;j++)
	if(!mask[j])
	  if((cards[i]%4)==(cards[j]%4))
	    for(size_t k = j+1;k<cards.size()-2;k++)
	      if(!mask[k])
		if((cards[i]%4)==(cards[k]%4))
		  for(size_t l = k+1;l<cards.size()-1;l++)
		    if(!mask[l])
		      if((cards[i]%4)==(cards[l]%4))
			for(size_t m = l+1;m<cards.size();m++)
			  if(!mask[m])
			    if((cards[i]%4)==(cards[m]%4)) {
			      for(size_t n = 0;n<mask.size();n++) 
				if((n==i)||(n==j)||(n==k)||(n==l)||(n==m))
				  mask[n] = false;
				else
				  mask[n] = true;
			      return true;
			    }
  return false;
}
bool CardTool::IsStraight(const Cards &cards, CardMasks& mask) {
  for(size_t i = 0;i<cards.size()-4;i++)
    if(!mask[i])
      for(size_t j = i+1;j<cards.size()-3;j++)
	if(!mask[j])
	  if((cards[i]/4)==(cards[j]/4+1))
	    for(size_t k = j+1;k<cards.size()-2;k++)
	      if(!mask[k])
		if((cards[j]/4)==(cards[k]/4+1))
		  for(size_t l = k+1;l<cards.size()-1;l++)
		    if(!mask[l])
		      if((cards[k]/4)==(cards[l]/4+1))
			for(size_t m = l+1;m<cards.size();m++)
			  if(!mask[m])
			    if((cards[l]/4)==(cards[m]/4+1))
			      return true;
  return false;
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
  result[name.size()+1]=' ';
  result[name.size()+2]='\0';
  switch(number) {
    case 0: // 1
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      result[name.size()] = '1'+number;
      break;
    case 8: // 10
      result[name.size()] = '1';
      result[name.size()+1] = '0';
      break;
    case 9:
      result[name.size()] = 'J';
    case 10:
      result[name.size()] = 'Q';
    case 11:
      result[name.size()] = 'K';
      break;
    case 12:
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
