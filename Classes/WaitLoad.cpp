//
//  WaitLoad.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/10/31.
//
//

#include "WaitLoad.hpp"
#include "ResourcesPath.h"

USING_NS_CC;

WaitLoad *WaitLoad::selfPointer = nullptr;

WaitLoad *WaitLoad::getInstance(){
    if (selfPointer == nullptr){
        selfPointer = create();
    }
    
    return selfPointer;
}

WaitLoad *WaitLoad::create(){
    CCLOG("建立 WaitLoad Layer， 这句如果重复输出，请处理多线程问题");
    WaitLoad *pRet = new (std::nothrow) WaitLoad();
    if (pRet && pRet->init()){
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool WaitLoad::init(){
    if (!Layer::init()){
        return false;
    }
    return true;
}

void WaitLoad::open(){
    if (isOpen){
        return;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    leftBackground->runAction(Sequence::create(MoveBy::create(0.3, Vec2(-visibleSize.width / 2, 0)),
                                               CallFuncN::create([&](Node *target){
        target->removeFromParent();
        isOpen = true;
    }), NULL));
    rightBackground->runAction(Sequence::create(MoveBy::create(0.3, Vec2(visibleSize.width / 2, 0)),
                                                CallFuncN::create([&](Node *target){
        target->removeFromParent();
        isOpen = true;
    }), NULL));
}

void WaitLoad::close(const std::function<void()> &callback){
    if (!isOpen){
        return;
    }
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/image/waitload/waitload_spritesheet.plist");
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    leftBackground = Sprite::createWithSpriteFrameName("waitload_background.png");
    leftBackground->setAnchorPoint(Vec2(1, 0));
    leftBackground->setPosition(0, 0);
    leftBackground->setGlobalZOrder(1000);
    this->addChild(leftBackground);
    
    leftLogo = Sprite::createWithSpriteFrameName("waitload_logo_left.png");
    leftLogo->setAnchorPoint(Vec2(1, 0.5));
    leftLogo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    leftLogo->setGlobalZOrder(1000);
    leftBackground->addChild(leftLogo);
    
    
    rightBackground = Sprite::createWithSpriteFrameName("waitload_background.png");
    rightBackground->setAnchorPoint(Vec2(1, 0));
    rightBackground->setScale(-1, 1);
    rightBackground->setPosition(visibleSize.width, 0);
    rightBackground->setGlobalZOrder(1000);
    this->addChild(rightBackground);
    
    rightLogo = Sprite::createWithSpriteFrameName("waitload_logo_right.png");
    rightLogo->setAnchorPoint(Vec2(0, 0.5));
    rightLogo->setScale(-1, 1);
    rightLogo->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    rightLogo->setGlobalZOrder(1000);
    rightBackground->addChild(rightLogo);
    
    leftBackground->runAction(Sequence::create(MoveBy::create(0.3, Vec2(visibleSize.width / 2, 0)),
                                               CallFunc::create([](){}),
                                               NULL));
    rightBackground->runAction(Sequence::create(MoveBy::create(0.3, Vec2(-visibleSize.width / 2, 0)),
                                                CallFuncN::create([=](Node *target){
        //这里引用捕获不行，值捕获行， 为什么？
        //因为函数传入的是引用值，值捕获捕获的是引用的值，引用捕获捕获到了引用的引用，而没有引用的引用这个东西
        callback();
        isOpen = false;
    }),NULL));
    
}

