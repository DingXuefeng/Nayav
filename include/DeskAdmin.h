/***********************************
 * Class: DeskAdmin
 *
 * Class for DeskAdmin
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef DeskAdmin_H
#define DeskAdmin_H
#include "IDeskAdmin.h"
#include "IPlayer.h"
#include <vector>
#include "Judger.h"
class DeskAdmin : public IDeskAdmin{
  public:
    void Participate(IPlayer *player) { m_players->push_back(player); };
    void StartNewDesk();
    void NewRounds();
    /*
    void PreFlop();
    void Flop();
    void Turn();
    void River();
    const int GetSmallBlind() const;
    const Cards *SendInhands();
    const Cards *GetFlop();
    const Card GetTurn();
    const Card GetRiver();
    const enum Round GetRounds();
    void Judge() const;
    */
  private:
    Players *m_players;
    IJudger *m_judger;

  private:
    DeskAdmin() : m_players(new Players), m_judger(new Judger) {};
    friend class Eimer;
    IJudger* GetJudger() const { return m_judger; };
    void SetJudger(IJudger* judger) { m_judger = judger; }
  class Result {
//    public:
//      void SetCards(Cards *cards) { m_cards = cards; }
//      bool operator<(const Result &left) const {
//	return left.m_marks<right.m_marks||
//	  ((left.m_marks==right.m_marks)&&(left.m_primaryCard<right.m_primaryCard));
//      }
//      bool operator==(const Result &left) const {
//	return ((left.m_marks==right.m_marks)&&
//	    (left.m_primaryCard==right.m_primaryCard));
//      }
////    Private:
//      Card flush() {
//      };
//      bool pair() {
//	for(size_t i = 0;i<m_cards.size()-1;i++)
//	  for(size_t j = i+1;j<m_cards.size();j++) {
//	    Cards left;
//	    left.push_back(m_cards[i]);
//	    left.push_back(m_cards[j]);
//	    if(CardTool::IsPair(left))
//	      return true;
//	  }
//	return false;
//      };
//      bool second_pair() {
//	for(size_t i = 0;i<m_cards.size()-1;i++)
//	  for(size_t j = i+1;j<m_cards.size();j++)
//	    if(CardTool::IsPair(m_cards[i],m_cards[j])) {
//	      Cards left;
//	      for(size_t k = 0;k<m_cards.size();k++)
//		if((k!=i)&&(k!=j)) left.push_back(m_cards[k]);
//	      Result left_r;
//	      left_r.m_cards = left;
//	      if(left_r.pair()) return true;
//	    }
//	return false;
//      };
//      Card three() {
//	if(m_cards.size()<3) return false;
//	for(size_t i = 0;i<m_cards.size()-2;i++)
//	  for(size_t j = i+1;j<m_cards.size()-1;j++) {
//	    Cards left;
//	    left.push_back(m_cards[i]);
//	    left.push_back(m_cards[j]);
//	    if(CardTool::IsPair(left))
//	      for(size_t k = j+1;k<m_cards.size();k++) {
//		Cards left;
//		left.push_back(m_cards[i]);
//		left.push_back(m_cards[k]);
//		if(CardTool::IsPair(left))
//		  return true;
//	      }
//	  }
//	return false;
//      }
//      Card four() {
//	if(m_cards.size()<4) return false;
//	for(size_t i = 0;i<m_cards.size()-3;i++)
//	  for(size_t j = i+1;j<m_cards.size()-2;j++)
//	    if(CardTool::IsPair(m_cards[i],m_cards[j]))
//	      for(size_t k = j+1;k<m_cards.size()-1;k++)
//		if(CardTool::IsPair(m_cards[i],m_cards[k]))
//		  for(size_t l = k+1;l<m_cards.size();l++)
//		    if(CardTool::IsPair(m_cards[i],m_cards[l]))
//		      return true;
//	return false;
//      }
//      Card straight() {
//	if(m_cards.size()<5) return false;
//	for(size_t m = 0;m<m_cards.size()-4;m++)
//	  for(size_t i = m+1;i<m_cards.size()-3;i++)
//	    for(size_t j = i+1;j<m_cards.size()-2;j++)
//	      for(size_t k = j+1;k<m_cards.size()-1;k++)
//		for(size_t l = k+1;l<m_cards.size();l++) {
//		  Cards left;
//		  left.push_back(m_cards[m]);
//		  left.push_back(m_cards[i]);
//		  left.push_back(m_cards[j]);
//		  left.push_back(m_cards[k]);
//		  left.push_back(m_cards[l]);
//		  if(CardTool::IsStraight(left)) return true;
//		}
//	return false;
//      }
//      Card flush() {
//	if(m_cards.size()<5) return false;
//	for(size_t m = 0;m<m_cards.size()-4;m++)
//	  for(size_t i = m+1;i<m_cards.size()-3;i++)
//	    for(size_t j = i+1;j<m_cards.size()-2;j++)
//	      for(size_t k = j+1;k<m_cards.size()-1;k++)
//		for(size_t l = k+1;l<m_cards.size();l++) {
//		  Cards left;
//		  left.push_back(m_cards[m]);
//		  left.push_back(m_cards[i]);
//		  left.push_back(m_cards[j]);
//		  left.push_back(m_cards[k]);
//		  left.push_back(m_cards[l]);
//		  if(CardTool::IsFlush(left)) return true;
//		}
//	return false;
//      }
//      Cards m_cards;
//      void CalMarks();
//      int m_marks;
//      Card m_primaryCard;
  };
  void Show(const Cards& pub,const std::map<IPlayer*,const Cards*>&) const;
};
#endif
