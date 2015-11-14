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

class Person : public cocos2d::Sprite{
public:
    
    Person(const std::string &name):
    _name(name) {};
    
    virtual void run() = 0;
    virtual void attack(Person *attackTarget) = 0;
    virtual void die() = 0;
    
protected:
    
    cocos2d::Sprite *_actionSprite;
    
    std::string _name;  //for example : desertThug
    std::string _side;  //for example : monster || soldier
    std::string _info;  //
    
    int _hp;
    int _speed;
    int _attackRange;
    
    int _numberOfAttackAnimationFrame;
    cocos2d::Vector<cocos2d::AnimationFrame *> _attackAniamtionFrameArray;
    int _numberOfDieAnimationFrame;
    cocos2d::Vector<cocos2d::AnimationFrame *> _dieAnimationFrameArray;
    int _numberOfForwardAnimationFrame;
    cocos2d::Vector<cocos2d::AnimationFrame *> _runForwardAnimationFrameArray;
    int _numberOfBackwardAnimationFrame;
    cocos2d::Vector<cocos2d::AnimationFrame *> _runBackwardAnimationFrameArray;
    int _numberOfTowardAnimationFrame;
    cocos2d::Vector<cocos2d::AnimationFrame *> _runTowardAnimationFrameArray;
    
    
};

#endif /* Person_hpp */
