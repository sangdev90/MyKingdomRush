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

class PersonActor;
class BattleLifeBarSprite;

class Person : public cocos2d::Sprite{
public:
    
    Person(const std::string &name):
    _name(name) {};
    
#pragma mark - Static Method
    
    static Person *createMonsterByName(const std::string &name, const std::vector<cocos2d::Vec2> &path);
    static Person *createSoldierByName(const std::string &name);
    
#pragma mark - Public None Virtual Method
    cocos2d::Size getActorSize();
    
#pragma mark - Pure Virtual Method
    
    virtual void run() = 0;
    virtual void attack(Person *attackTarget) = 0;
    virtual void die() = 0;
    virtual void loseBlood(int loseBloodValue) = 0; //TODO:这里是不是要一个非纯虚函数
    virtual void addBlood(int addBloodValue) = 0;   //TODO:这里是不是要一个非纯虚函数
    
#pragma mark - Impure Virtual Method
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
#pragma mark - Public Data Member
    
    bool isDie = false;
    
protected:
    
    PersonActor *_personActor;
    BattleLifeBarSprite *_lifeBar;
    
    std::string _name;  //for example : desertThug
    std::string _side;  //for example : monster || soldier
    std::string _info;  //
    
    int _hp = 100;
    int _runSpeed = 10;
    int _attackRange = 50;
    
//    cocos2d::EventListenerTouchOneByOne *_touchListener;
//    void _addTouchListener();
    
};

#endif /* Person_hpp */
