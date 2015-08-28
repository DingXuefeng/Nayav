/***********************************
 * Class: Card
 *
 * Class for Card
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Card_H
#define Card_H
typedef int Card;
#include <vector>
typedef std::vector<Card> Cards;
typedef std::vector<bool> CardMasks;
typedef std::vector<bool> CardMasks;
#include <map>
class IPlayer;
typedef std::map<IPlayer*,const Cards*> Inhands;
#endif
