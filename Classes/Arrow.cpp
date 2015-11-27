//
//  Arrow.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/26.
//
//

#include "Arrow.hpp"
#include "ToolFunction.hpp"
USING_NS_CC;

Arrow *Arrow::createArrowByLevel(const std::string &level){
    
    Arrow *newArrow = new (std::nothrow) Arrow(level);
    if (newArrow && newArrow->initArrow()){
        newArrow->autorelease();
        return newArrow;
    }
    
    delete newArrow;
    newArrow = nullptr;
    return nullptr;
    
}

bool Arrow::initArrow(){
    
    if (!this->initWithSpriteFrameName(getTowerShootThingSpriteFrameNameByNameAndLevel(_name, _level))){
        return false;
    }
    
    return true;
    
}

void Arrow::attack(const cocos2d::Vec2 &from, const cocos2d::Vec2 &to, const std::function<void ()> &attackCallback){
    
    //传进来的坐标点应该是在塔的坐标系下的坐标
    
    if (_level == "level1" || _level == "level2" || _level == "level3"){
        float Y = 50;
        Vec2 middlePoint = Vec2(from.x + 0.5 * (to.x - from.x), Y + to.y);
        
        MoveTo *firstHalfMoveToAction = MoveTo::create(0.3, middlePoint);
        MoveTo *secondHalfMoveToAction = MoveTo::create(0.3, to);
        RotateBy *firstHalfRotateAction;
        RotateBy *secondHalfRotateAction;
        if (from.x > to.x){
            firstHalfRotateAction = RotateBy::create(0.3, -90);
            secondHalfRotateAction = RotateBy::create(0.3, -90);
        }else {
            firstHalfRotateAction = RotateBy::create(0.3, 90);
            secondHalfRotateAction = RotateBy::create(0.3, 90);
        }
        
        this->runAction(Sequence::create(
                                         Spawn::create(firstHalfMoveToAction, firstHalfRotateAction, NULL),
                                         Spawn::create(secondHalfMoveToAction, secondHalfRotateAction, NULL),
                                         CallFuncN::create([&](Node *target){
                                            CCLOG("箭射完了");
//                                            attackCallback();
                                         }),
                                         NULL));
        
    }
    //TODO: 11,27 从这里开始，现在的状态是低级射箭的动作刚做完
    
}
