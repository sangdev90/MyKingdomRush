//
//  Person.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/11.
//
//

#include "Person.hpp"
#include "ResourcesPath.h"
#include "ToolFunction.hpp"
#include "Behavior.hpp"
#include "PersonActor.hpp"

USING_NS_CC;

bool Person::init(){
    if (!Sprite::init()){
        return false;
    }
    
    return true;
}

void Person::onEnter(){
    Sprite::onEnter();
//    _addTouchListener();
}

void Person::onExit(){
    Sprite::onExit();
//    if (_touchListener){
//        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
//    }
}

Size Person::getActorSize(){
    Size actorSize = _personActor->getContentSize();
    if (actorSize.width == 0 || actorSize.height == 0){
        return Size(50, 50);
    }else {
        return actorSize;
    }
}

//void Person::_addTouchListener(){
//    _touchListener = EventListenerTouchOneByOne::create();
//    _touchListener->setSwallowTouches(false);
//    _touchListener->onTouchBegan = [&](Touch *touch, Event *event){
//        Vec2 location = convertToNodeSpace(touch->getLocation());
//        Size selfSize = _personActor->getContentSize();
//        if (selfSize.width == 0 || selfSize.height == 0){
//            selfSize.width = 50;
//            selfSize.height = 50;
//        }
//        Rect selfRect = Rect(0, 0, selfSize.width, selfSize.height);
//        if (selfRect.containsPoint(location)){
////            CCLOG("点击了 Person");
//        }else {
////            CCLOG("没点击 Person");
//        }
//        return false;
//    };
//    _touchListener->onTouchMoved = [&](Touch *touch, Event *event){
//        
//    };
//    _touchListener->onTouchEnded = [&](Touch *touch, Event *event){};
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
//}