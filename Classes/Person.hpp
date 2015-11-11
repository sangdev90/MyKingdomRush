//
//  Person.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/11.
//
//

#ifndef Person_hpp
#define Person_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ResourcesPath.h"
#include "ToolFunction.cpp"
#include "Behavior.hpp"

class Person : public cocos2d::Sprite{
public:
    
    void setName(const std::string &name);
    const std::string &getName();
    void setSide(const std::string &side);
    const std::string &getSide();
    
private:
    
    std::string _name;  //for example : desertthug
    std::string _side;  //for example : enemy || soldier
    std::string _info;  //
    
    int hp;
    
};

#endif /* Person_hpp */
