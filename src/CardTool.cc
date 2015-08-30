#include "CardTool.h"
#include <stdexcept>
#include <iostream>
using std::cout;
using std::endl;
const std::string CardTool::ToType(int rank) {
  int i = 0;
  while(rank>13) {
    rank = rank/14;
    i++;
  }
  std::string type;
  switch(i) {
    case 0:
      type = "High card"; break;
    case 1:
      type = "One pair"; break;
    case 2:
      type = "Two pair"; break;
    case 3:
      type = "Three of a kind"; break;
    case 4:
      type = "Straight"; break;
    case 5:
      type = "Flush"; break;
    case 6:
      type = "Full house"; break;
    case 7:
      type = "Four"; break;
    case 8:
      if(rank==12)
	type = "Royal flush straight";
      else
	type = "Flush straight";
      break;
    default:
      type = "Unknown"; break;
  }
  type.append(" ");
  type.append(GetNumberName(rank-1)); 
  return type;
}
#include <cstring>
#include <cmath>
const int CardTool::Rank(const Cards &cards) {
  CardMasks _mask(7,false);
  Cards _cards(cards.size());
  std::copy(cards.begin(),cards.end(),_cards.begin());
  for(size_t i = 0;i<_cards.size()-1;i++)
    for(size_t j = i+1;j<_cards.size();j++)
      if(_cards[i]/4<_cards[j]/4) {
	Card tmp = _cards[i];
	_cards[i] = _cards[j];
	_cards[j] = tmp;
      }
  char* mark = new char[6];
  memset(mark,0,6);
  mark[6] = IsFlush(_cards,_mask);
  mark[5] = IsStraight(_cards,_mask);
  mark[4] = IsFour(_cards,_mask);
  mark[3] = IsThree(_cards,_mask);
  mark[2] = IsPair(_cards,_mask);
  mark[1] = IsPair(_cards,_mask);
  mark[0] = _cards[0]/4+1;
  int final_mark = mark[6]*(mark[5]>0)*pow(14,8)+
    mark[4]*pow(14,7)+mark[3]*(mark[2]>0)*pow(14,6)+mark[6]*pow(14,5)+
    mark[5]*pow(14,4)+mark[3]*pow(14,3)+
    mark[2]*((mark[1]>0)*13+1)*14+mark[1]*14+
    mark[0];
  return final_mark;
}
//throw std::runtime_error("Is pair only accepts 2 cards.");
//
const int CardTool::IsFlush(const Cards &cards, CardMasks& mask) {
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
			      return cards[i]/4+1;
			    }
  return 0;
}

const int CardTool::IsStraight(const Cards &cards, CardMasks& mask) {
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
			    if((cards[l]/4)==(cards[m]/4+1)) {
			      for(size_t n = 0;n<mask.size();n++) 
				mask[n] = true;
			      return cards[i]/4+1;
			    }
  return 0;
}

const int CardTool::IsFour(const Cards &cards,CardMasks& mask) {
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
		      if(cards[i]/4==cards[l]/4) {
			for(size_t n = 0;n<mask.size();n++) 
			  mask[n] = true;
			return cards[i]/4+1;
		      }
  return 0;
}

const int CardTool::IsThree(const Cards &cards,CardMasks& mask) {
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
		  return cards[i]/4+1;
		}
  return 0;
}

const int CardTool::IsPair(const Cards &cards,CardMasks& mask) {
  for(size_t i = 0;i<cards.size()-1;i++)
    if(!mask[i])
      for(size_t j = i+1;j<cards.size();j++)
	if(!mask[j])
	  if(cards[i]/4==cards[j]/4) {
	    mask[i] = true;
	    mask[j] = true;
	    return cards[i]/4+1;
	  }
  return 0;
}

const char* CardTool::GetRoundName(const int round) {
  switch(round) {
    case IDeskAdmin::pre_flop:
      return "Pr F"; break;
    case IDeskAdmin::flop:
      return "Flop"; break;
    case IDeskAdmin::turn:
      return "Turn"; break;
    case IDeskAdmin::river:
      return "Rivr"; break;
    default:
      return "Err."; break;
  }
}

const char* CardTool::GetName(Card card) {
  const int color = card%4; 
  std::deque<char> name;
  switch(color) {
    case 0: // Diamond
      name = unicode_to_utf8(0x2666);
      break;
    case 1: // Club
      name = unicode_to_utf8(0x2663);
      break;
    case 2: // Heart
      name = unicode_to_utf8(0x2665);
      break;
    case 3: // Spade
      name = unicode_to_utf8(0x2660);
      break;
    default:
      break;
  }
  char* result = new char[name.size()+3];
  std::copy(name.begin(),name.end(),result);
  const char* number_name = GetNumberName(card/4);
  std::copy(number_name,number_name+3,result+name.size());
  return result;
}

const char* CardTool::GetNumberName(int number) {
  char* result = new char[3];
  result[1]=' ';
  result[2]='\0';
  switch(number) {
    case 0: // 2
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
    case 7:
      result[0] = '2'+number;
      break;
    case 8: // 10
      result[0] = '1';
      result[1] = '0';
      break;
    case 9:
      result[0] = 'J';
      break;
    case 10:
      result[0] = 'Q';
      break;
    case 11:
      result[0] = 'K';
      break;
    case 12:
      result[0] = 'A';
      break;
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
