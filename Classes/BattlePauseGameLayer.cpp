//
//  BattlePauseGameLayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/29.
//
//

#include "BattlePauseGameLayer.hpp"
#include "ResourcesPath.h"
#include "ToolFunction.hpp"
#include "StateButton.hpp"

USING_NS_CC;

BattlePauseGameLayer *BattlePauseGameLayer::createBattlePauseGameLayer(){
    
    BattlePauseGameLayer *battlePauseGameLayer = new (std::nothrow) BattlePauseGameLayer();
    
    if (battlePauseGameLayer && battlePauseGameLayer->init()){
        battlePauseGameLayer->autorelease();
        return battlePauseGameLayer;
    }
    
    delete battlePauseGameLayer;
    battlePauseGameLayer = nullptr;
    return nullptr;
    
}

#pragma mark - Public Method

bool BattlePauseGameLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    _layoutUI();
    
    return true;
}

void BattlePauseGameLayer::onEnter(){
    Layer::onEnter();
}

void BattlePauseGameLayer::onExit(){
    Layer::onExit();
}

void BattlePauseGameLayer::show(const std::function<void ()> &callback){
    _grayBackgroundLayer->setVisible(true);
    _backgroundLayer->setVisible(true);
    
    _backgroundLayer->runAction(Sequence::create(MoveTo::create(0.5, Vec2(0, 0)),
                                                 CallFuncN::create([&, callback](Node *target){
        this->_addSwallowTouchListener();
        callback();
    }),
                                                 NULL));
}

void BattlePauseGameLayer::close(const std::function<void ()> &callback){
    _backgroundLayer->runAction(Sequence::create(MoveTo::create(0.5, Vec2(0, Director::getInstance()->getVisibleSize().height)),
                                                 CallFuncN::create([&, callback](Node *target){
        this->_removeSwallowtouchListener();
        callback();
    }),
                                                 NULL));
}

#pragma mark - Private Method

void BattlePauseGameLayer::_layoutUI(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _grayBackgroundLayer = LayerColor::create(Color4B(0, 0, 0, 100), visibleSize.width, visibleSize.height);
    _grayBackgroundLayer->setPosition(0, 0);
    this->addChild(_grayBackgroundLayer, 0);
    _grayBackgroundLayer->setVisible(false);
    
    
    _backgroundLayer = Layer::create();
    _backgroundLayer->setPosition(0, visibleSize.height);
    this->addChild(_backgroundLayer, 1);
    _backgroundLayer->setVisible(false);
    
    
    Sprite *leftChain = Sprite::createWithSpriteFrameName("battle_ui_chain.png");
    Sprite *rightChain = Sprite::createWithSpriteFrameName("battle_ui_chain.png");
    leftChain->setAnchorPoint(Vec2(0.5, 1));
    rightChain->setAnchorPoint(Vec2(0.5, 1));
    rightChain->setFlippedX(true);
    leftChain->setPosition(visibleSize.width / 2 - 178, visibleSize.height);
    rightChain->setPosition(visibleSize.width / 2 + 178, visibleSize.height);
    _backgroundLayer->addChild(leftChain, 1);
    _backgroundLayer->addChild(rightChain, 1);
    
    
    Sprite *boardTop = Sprite::createWithSpriteFrameName("battle_ui_board_top.png");
    Sprite *boardButtom = Sprite::createWithSpriteFrameName("battle_ui_board_top.png");
    Sprite *boardCenter1 = Sprite::createWithSpriteFrameName("battle_ui_board_normal.png");
    Sprite *boardCenter2 = Sprite::createWithSpriteFrameName("battle_ui_board_normal.png");
    Sprite *boardCenter3 = Sprite::createWithSpriteFrameName("battle_ui_board_normal.png");
    
    boardTop->setAnchorPoint(Vec2(0.5, 1));
    boardButtom->setAnchorPoint(Vec2(0.5, 1));
    boardCenter1->setAnchorPoint(Vec2(0.5, 1));
    boardCenter2->setAnchorPoint(Vec2(0.5, 1));
    boardCenter3->setAnchorPoint(Vec2(0.5, 1));
    
    boardTop->setPosition(    visibleSize.width / 2, visibleSize.height - leftChain->getContentSize().height + 20);
    boardCenter1->setPosition(visibleSize.width / 2, boardTop->getPosition().y - boardTop->getContentSize().height + 2);
    boardCenter2->setPosition(visibleSize.width / 2, boardCenter1->getPosition().y - boardCenter1->getContentSize().height + 2);
    boardCenter3->setPosition(visibleSize.width / 2, boardCenter2->getPosition().y - boardCenter2->getContentSize().height + 2);
    boardButtom->setPosition( visibleSize.width / 2, boardCenter3->getPosition().y - boardCenter3->getContentSize().height + 2);
    boardButtom->setFlippedY(true);
    
    _backgroundLayer->addChild(boardTop, 1);
    _backgroundLayer->addChild(boardCenter1, 1);
    _backgroundLayer->addChild(boardCenter2, 1);
    _backgroundLayer->addChild(boardCenter3, 1);
    _backgroundLayer->addChild(boardButtom, 1);
    
    Size viewSize = boardCenter1->getContentSize();
    float offsetX = viewSize.width / 3 - 50;
    
    Sprite *iconBackground1 = Sprite::createWithSpriteFrameName("battle_ui_icon_background.png");
    iconBackground1->setPosition(visibleSize.width / 2 - offsetX, 350);
    _backgroundLayer->addChild(iconBackground1, 2);
    
    Sprite *iconBackground2 = Sprite::createWithSpriteFrameName("battle_ui_icon_background.png");
    iconBackground2->setPosition(visibleSize.width / 2, 350);
    _backgroundLayer->addChild(iconBackground2, 2);
    
    Sprite *iconBackground3 = Sprite::createWithSpriteFrameName("battle_ui_icon_background.png");
    iconBackground3->setPosition(visibleSize.width / 2 + offsetX, 350);
    _backgroundLayer->addChild(iconBackground3, 2);
    
    //TODO:下面几个按钮的 callback
    
    StateButton *musicButton = StateButton::createStateButton("battle_ui_icon_sound.png", "battle_ui_icon_close.png");
    musicButton->setState(StateButtonOn);
    musicButton->setChangeToOnCallback([&](){
        CCLOG("Music On!");
    });
    musicButton->setChangeToOffCallback([&](){
        CCLOG("Music Off!");
    });
    musicButton->setPosition(iconBackground1->getPosition());
    _backgroundLayer->addChild(musicButton, 3);
    
    StateButton *soundButton = StateButton::createStateButton("battle_ui_pause_icon_music.png", "battle_ui_icon_close.png");
    soundButton->setState(StateButtonOn);
    soundButton->setChangeToOnCallback([&](){
        CCLOG("Sound On!");
    });
    soundButton->setChangeToOffCallback([&](){
        CCLOG("Sound Off!");
    });
    soundButton->setPosition(iconBackground2->getPosition());
    _backgroundLayer->addChild(soundButton, 3);
    
    StateButton *vibrateButton = StateButton::createStateButton("battle_ui_icon_vibrate.png", "battle_ui_icon_close.png");
    vibrateButton->setState(StateButtonOn);
    vibrateButton->setChangeToOnCallback([&](){
        CCLOG("Vibrate On!");
    });
    vibrateButton->setChangeToOffCallback([&](){
        CCLOG("Vibrate Off!");
    });
    vibrateButton->setPosition(iconBackground3->getPosition());
    _backgroundLayer->addChild(vibrateButton, 3);
    
    ui::Button *restartButton = createScaleButtonWithTwoSpriteFrameNameAndCallback("battle_ui_button_restart.png", "battle_ui_button_restart.png", [&](Ref *sender, ui::Widget::TouchEventType touchType){
        if (touchType == ui::Widget::TouchEventType::ENDED){
            CCLOG("Restart");
        }
    });
    restartButton->setPosition(Vec2(visibleSize.width / 2 - 200, 200));
    _backgroundLayer->addChild(restartButton, 2);
    
    ui::Button *quitButton = createScaleButtonWithTwoSpriteFrameNameAndCallback("battle_ui_button_quit.png", "battle_ui_button_quit.png", [&](Ref *sender, ui::Widget::TouchEventType touchType){
        if (touchType == ui::Widget::TouchEventType::ENDED){
            CCLOG("Quit");
        }
    });
    quitButton->setPosition(Vec2(visibleSize.width / 2 + 200, 200));
    _backgroundLayer->addChild(quitButton, 2);
    
    ui::Button *closeButton = createButtonWithTwoSpriteFrameNameAndCallback("battle_ui_button_close.png", "battle_ui_button_close_on.png", [&](Ref *sender, ui::Widget::TouchEventType touchType){
        if (touchType == ui::Widget::TouchEventType::ENDED){
            CCLOG("Close!");
        }
    });
    closeButton->setPosition(Vec2(visibleSize.width / 2 + 400, 500));
    _backgroundLayer->addChild(closeButton, 2);
    
}

void BattlePauseGameLayer::_addSwallowTouchListener(){
    _swallowTouchListener = cocos2d::EventListenerTouchOneByOne::create();
    _swallowTouchListener->setSwallowTouches(true);
    _swallowTouchListener->onTouchBegan = [](Touch *touch, Event *event){
        return true;
    };
    _swallowTouchListener->onTouchMoved = [](Touch *touch, Event *event){};
    _swallowTouchListener->onTouchEnded = [](Touch *touch, Event *event){};
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_swallowTouchListener, this);
}

void BattlePauseGameLayer::_removeSwallowtouchListener(){
    if (_swallowTouchListener){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_swallowTouchListener);
    }
}