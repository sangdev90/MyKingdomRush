//
//  Credits.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/2.
//
//

#include <iostream>

#include "Credits.hpp"

#include "ResourcesPath.h"
#include "WaitLoad.hpp"
#include "ToolFunction.hpp"
#include "MainMenu.hpp"

#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/document.h"

USING_NS_CC;

Scene *Credits::createScene(){
    Scene *scene = Scene::create();
    Credits *layer = Credits::create();
    scene->addChild(layer);
    return scene;
}

Credits *Credits::create(){
    Credits *pRet = new (std::nothrow) Credits();
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool Credits::init(){
    if (!Layer::init()){
        return false;
    }
    
    this->addChild(WaitLoad::getInstance(), 100);
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CREDITS_UI_PLIST);
    
    this->scrollView = ui::ScrollView::create();
    this->calculateScrollViewHeight();
    
    
    return true;
}

void Credits::onEnter(){
    Layer::onEnter();
    CCLOG("Credits onEnter");
    WaitLoad::getInstance()->open();
    this->scheduleUpdate();
}

void Credits::onExit(){
    Layer::onExit();
    this->unscheduleUpdate();
}

void Credits::update(float dt){
    scrollView->scrollToBottom(scrollView->getInnerContainerSize().height / 20, true);
}

void Credits::parseCreditsData(){
    
    std::string jsonPath = FileUtils::getInstance()->fullPathForFilename(CREDITS_DATA_JSON);
    std::string jsonData = FileUtils::getInstance()->getStringFromFile(jsonPath);
    
    CCLOG("%s", jsonData.c_str());
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(jsonData.c_str());
    if (jsonDocument.HasParseError()){
        CCLOG("Parse Credits Data Error %u", jsonDocument.GetParseError());
    }else {
        if (jsonDocument.IsArray()){
            for (int index = 0; index < jsonDocument.Size(); ++index){
                if (jsonDocument[index].IsObject()){
                    //                    CCLOG("%s", jsonDocument[index]["title"].GetString());
                    //构造 STL 数据结构，便于使用
                    std::vector<std::string> names;
                    if (jsonDocument[index]["names"].IsArray()){
                        for (int nameIndex = 0; nameIndex < jsonDocument[index]["names"].Size(); ++nameIndex){
                            names.push_back(jsonDocument[index]["names"][nameIndex].GetString());
                            //                            CCLOG("%s", jsonDocument[index]["names"][nameIndex].GetString());
                        }
                        
                        CreditsData credit(jsonDocument[index]["title"].GetString(), names);
                        this->creditData.push_back(credit);
                    }
                }
            }
        }
    }
    
    CCLOG("STL 中的数据");
    for (auto iterator = creditData.begin(); iterator != creditData.end(); ++iterator){
        CCLOG("%s", iterator->title.c_str());
        for (auto nameIterator = iterator->names.begin(); nameIterator != iterator->names.end(); ++nameIterator){
            std::cout << nameIterator->c_str() << " ";
        }
        std::cout << std::endl;
    }
    
}

void Credits::calculateScrollViewHeight(){
    
    scrollViewHeight = 0;
    
    this->parseCreditsData();
    
    Label *testTitleLabel = Label::createWithSystemFont("TestTitle", "Arial", titleSize);
    Label *testNameLabel = Label::createWithSystemFont("TestName", "Arial", nameSize);
    
    float titleHeight = testTitleLabel->getContentSize().height;
    float nameHeight = testNameLabel->getContentSize().height;
    
    float creditHeight = 0;
    for (auto iterator = creditData.begin(); iterator != creditData.end(); ++iterator){
        creditHeight += titleHeight;
        creditHeight += nameHeight * iterator->names.size();
    }
    
    theNumberOfBackground = creditHeight / (Sprite::createWithSpriteFrameName("credits_background.png")->getContentSize().height);
    ++theNumberOfBackground;
    
    CCLOG("Need %d background", theNumberOfBackground);
    
    this->layout();
    
}

void Credits::layout(){
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    //布局 UI 元素
    
    studioLogo = Sprite::createWithSpriteFrameName("credits_icon_studio.png");
    cocosLogo  = Sprite::createWithSpriteFrameName("credits_icon_cocos.png");
    backgroundTop = Sprite::createWithSpriteFrameName("credits_background_top.png");
    backgroundButtom = Sprite::createWithSpriteFrameName("credits_background_top.png");
    
    float backgroundItemHeight = Sprite::createWithSpriteFrameName("credits_background.png")->getContentSize().height;
    
    scrollViewHeight = backgroundTop->getContentSize().height * 2 + theNumberOfBackground * backgroundItemHeight;
    
    scrollView = ui::ScrollView::create();
    scrollView->setBounceEnabled(false);
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setAnchorPoint(Vec2(0.5, 0.5));
    scrollView->cocos2d::Node::setPosition(visibleSize.width / 2, visibleSize.height / 2);
    scrollView->setContentSize(visibleSize);
    scrollView->setInnerContainerSize(Size(visibleSize.width, scrollViewHeight));
    this->addChild(scrollView, 1);
    
    backgroundTop->setAnchorPoint(Vec2(0.5, 0));
    backgroundButtom->setAnchorPoint(Vec2(0.5, 0));
    
    backgroundButtom->setPosition(visibleSize.width / 2, 0);
    backgroundButtom->setFlippedY(true);
    scrollView->addChild(backgroundButtom, 1);
    float buttomHeight = backgroundButtom->getContentSize().height;
    for (int itemIndex = 0; itemIndex < theNumberOfBackground; ++itemIndex){
        Sprite *itemBackgound = Sprite::createWithSpriteFrameName("credits_background.png");
        itemBackgound->setAnchorPoint(Vec2(0.5, 0));
        itemBackgound->setPosition(visibleSize.width / 2, itemIndex * backgroundItemHeight + buttomHeight - itemIndex - 1);
        scrollView->addChild(itemBackgound, 1);
    }
    backgroundTop->setAnchorPoint(Vec2(0.5, 0));
    backgroundTop->setPosition(visibleSize.width / 2, buttomHeight + theNumberOfBackground * backgroundItemHeight - 10);
    scrollView->addChild(backgroundTop, 1);
    
    studioLogo->setPosition(visibleSize.width / 2, buttomHeight / 2);
    backgroundTop->addChild(studioLogo, 1);
    
    cocosLogo->setPosition(visibleSize.width / 2, buttomHeight / 2);
    backgroundButtom->addChild(cocosLogo, 1);
    
    swordIcon = Sprite::createWithSpriteFrameName("credits_icon_sword.png");
    swordIcon->setPosition(Vec2(visibleSize.width - swordIcon->getContentSize().width / 2, scrollViewHeight - swordIcon->getContentSize().height / 2));
    scrollView->addChild(swordIcon, 10);
    
    backButton = createMenuWithSpriteByThreeTextureAndCallback("credits_button_back.png",
                                                               "credits_button_back_on.png",
                                                               "credits_button_back_on.png",
                                                               [](Ref *sender){
                                                                   CCLOG("Credit Back Button");
                                                                   WaitLoad::getInstance()->close([](){
                                                                       Scene *mainMenuScene = MainMenu::createScene(false);
                                                                       Director::getInstance()->replaceScene(mainMenuScene);
                                                                   });
                                                               });
    backButton->setPosition(100, 80);
    this->addChild(backButton, 10);
    
    //布局文字元素
    
    float startLayoutHeight = buttomHeight + theNumberOfBackground * backgroundItemHeight;
    float lastItemHeight = 0;
    for (auto iterator = creditData.begin(); iterator != creditData.end(); ++iterator){
        Label *titleLabel = Label::createWithSystemFont(iterator->title, "Arial", titleSize);
        titleLabel->setPosition(visibleSize.width / 2, startLayoutHeight - lastItemHeight);
        titleLabel->setTextColor(Color4B::BLACK);
        scrollView->addChild(titleLabel, 5);
        int nameItemHeight = 0;
        for (auto nameIterator = iterator->names.begin(); nameIterator != iterator->names.end(); ++nameIterator){
            Label *nameLabel = Label::createWithSystemFont(*nameIterator, "Arial", nameSize);
            nameLabel->setTextColor(Color4B::BLACK);
            nameItemHeight = nameLabel->getContentSize().height;
            nameLabel->setPosition(visibleSize.width / 2, titleLabel->getPosition().y - titleLabel->getContentSize().height - (nameIterator - iterator->names.begin()) * nameItemHeight);
            scrollView->addChild(nameLabel, 5);
        }
        lastItemHeight += titleLabel->getContentSize().height + nameItemHeight * iterator->names.size() + 30;
    }
    
}

