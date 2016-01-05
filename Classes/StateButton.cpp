//
//  StateButton.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 16/1/2.
//
//

#include "StateButton.hpp"

USING_NS_CC;

StateButton *StateButton::createStateButton(const std::string &iconSpriteFrameName, const std::string &offIconSpriteFrameName){
    StateButton *stateButton = new (std::nothrow) StateButton();
    if (stateButton && stateButton->initWithTwoSpriteFrameName(iconSpriteFrameName, offIconSpriteFrameName)){
        stateButton->autorelease();
        return stateButton;
    }
    
    delete stateButton;
    stateButton = nullptr;
    return nullptr;
}

bool StateButton::initWithTwoSpriteFrameName(const std::string &iconSpriteFrameName, const std::string &offIconSpriteFrameName){
    if (!Sprite::initWithSpriteFrameName(iconSpriteFrameName)){
        return false;
    }
    
    _offIcon = Sprite::createWithSpriteFrameName(offIconSpriteFrameName);
    _offIcon->setPosition(this->getContentSize().width - 20, 20);
    this->addChild(_offIcon, 1);
    _offIcon->setVisible(false);
    
    return true;
}

void StateButton::onEnter(){
    Sprite::onEnter();
    
    _addTouchListener();
}

void StateButton::onExit(){
    Sprite::onExit();
    
    if (_touchListener){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
    }
}

void StateButton::changeState(){
    if (_state == StateButtonOn){
        _state = StateButtonOff;
        _offIcon->setVisible(true);
        _changeToOffCallback();
    }else {
        _state = StateButtonOn;
        _offIcon->setVisible(false);
        _changeToOnCallback();
    }
}

void StateButton::setState(int state){
    if (state == StateButtonOn){
        _state = StateButtonOn;
        _offIcon->setVisible(false);
        _changeToOnCallback();
    }else if (state == StateButtonOff){
        _state = StateButtonOff;
        _offIcon->setVisible(true);
        _changeToOffCallback();
    }
}

void StateButton::setChangeToOnCallback(const std::function<void ()> &callback){
    _changeToOnCallback = callback;
}

void StateButton::setChangeToOffCallback(const std::function<void ()> &callback){
    _changeToOffCallback = callback;
}

void StateButton::_addTouchListener(){
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = [&](Touch *touch, Event *event){
        Vec2 locationPostion = this->convertToNodeSpace(touch->getLocation());
        Size selfSize = this->getContentSize();
        if (selfSize.width == 0 || selfSize.height == 0){
            selfSize.width = 50;
            selfSize.height = 50;
        }
        Rect selfRect = Rect(0, 0, selfSize.width, selfSize.height);
        if (selfRect.containsPoint(locationPostion)){
            _touchBegan = true;
            return true;
        }
        return false;
    };
    _touchListener->onTouchMoved = [&](Touch *touch, Event *event){};
    _touchListener->onTouchEnded = [&](Touch *touch, Event *event){
        Vec2 locationPostion = this->convertToNodeSpace(touch->getLocation());
        Size selfSize = this->getContentSize();
        if (selfSize.width == 0 || selfSize.height == 0){
            selfSize.width = 50;
            selfSize.height = 50;
        }
        Rect selfRect = Rect(0, 0, selfSize.width, selfSize.height);
        if (selfRect.containsPoint(locationPostion) && _touchBegan == true){
            this->changeState();
        }
    };
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
}

