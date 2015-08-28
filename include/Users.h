/***********************************
 * Class: Users
 *
 * Class for Users
 * Author: Ding XueFeng
 * Email: dxf317550678@gmail.com
 ***********************************/

#ifndef Users_H
#define Users_H
#include <string>
#include "Human.h"
class Users{
  public:
    static IPlayer* Loggin(const std::string username,const std::string passwd) {
      if(username == "dingxf" && passwd == "passwd")
	return new Human(1000,false,0,"Ding X F");
      else
	return NULL;
    };
};
#endif
