//
//  BattleUILayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include "BattleUILayer.hpp"
#include "ToolFunction.hpp"
#include "BattleDisplayBoardSprite.hpp"
#include "BattlePauseGameLayer.hpp"

USING_NS_CC;

BattleUILayer *BattleUILayer::create(){
    BattleUILayer *pRet = new (std::nothrow) BattleUILayer();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BattleUILayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    this->_layoutUI();
    
    //MARK:Test
    _someTestCode();
    
    return true;
}

void BattleUILayer::_layoutUI(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _displayBoardSprite = BattleDisplayBoardSprite::createWithInformationAndSpriteFrameName(20, 500, 1, 10, "battle_ui_displayboard.png");
    _displayBoardSprite->setAnchorPoint(Vec2(0, 1));
    _displayBoardSprite->setPosition(20, visibleSize.height - 20);
    this->addChild(_displayBoardSprite, 1);
    
    _pauseGameLayer = BattlePauseGameLayer::createBattlePauseGameLayer();
    _pauseGameLayer->setPosition(Vec2(0, 0));
    this->addChild(_pauseGameLayer, 100);
    
    _pauseGameButton = ui::Button::create();
    _pauseGameButton->setTouchEnabled(true);
    _pauseGameButton->loadTextures("battle_ui_button_pause.png", "battle_ui_button_pause_on.png", "", ui::TextureResType::PLIST);
    _pauseGameButton->setPosition(Vec2(visibleSize.width - 50, visibleSize.height - 40));
    _pauseGameButton->addTouchEventListener(static_cast<ui::Widget::ccWidgetTouchCallback>(CC_CALLBACK_2(BattleUILayer::_pauseButtonTouchListener, this)));
    this->addChild(_pauseGameButton, 1);
    
}

void BattleUILayer::_pauseButtonTouchListener(cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType touchType){
    switch (touchType){
        case ui::Widget::TouchEventType::BEGAN:{
            break;
        }
        case ui::Widget::TouchEventType::MOVED:{
            break;
        }
        case ui::Widget::TouchEventType::ENDED:{
            CCLOG("Pause Game!");
            _pauseGameLayer->show([](){});
            break;
        }
        case ui::Widget::TouchEventType::CANCELED:{
            break;
        }
    }
}

void BattleUILayer::_someTestCode(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //TTF 字体测试
//    Label *testFrontLabel0 = createTTFLabelWithFrontName("Comic_Book 1234567890", 30, front_comic_book, Color3B(0, 0, 0));
//    testFrontLabel0->setPosition(visibleSize.width / 2, visibleSize.height - 50);
//    this->addChild(testFrontLabel0, 100);
//    
//    Label *testFrontLabel1 = createTTFLabelWithFrontName("ObelixPro 1234567890", 30, front_obelix_pro, Color3B(0, 0, 0));
//    testFrontLabel1->setPosition(visibleSize.width / 2, visibleSize.height - 100);
//    this->addChild(testFrontLabel1, 100);
//    
//    Label *testFrontLabel2 = createTTFLabelWithFrontName("SohoGothicProMedium 1234567890", 30, front_soho_gothic_pro_medium, Color3B(0, 0, 0));
//    testFrontLabel2->setPosition(visibleSize.width / 2, visibleSize.height - 150);
//    this->addChild(testFrontLabel2, 100);
//    
//    Label *testFrontLabel3 = createTTFLabelWithFrontName("TOONISH 1234567890", 30, front_toonish, Color3B(0, 0, 0));
//    testFrontLabel3->setPosition(visibleSize.width / 2, visibleSize.height - 200);
//    this->addChild(testFrontLabel3, 100);
//    
//    Label *testFrontLabel4 = createTTFLabelWithFrontName("YIKES 1234567890", 30, front_yikes, Color3B(0, 0, 0));
//    testFrontLabel4->setPosition(visibleSize.width / 2, visibleSize.height - 250);
//    this->addChild(testFrontLabel4, 100);
    
}
