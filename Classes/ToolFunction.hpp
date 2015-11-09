//
//  ToolFunction.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/10/31.
//
//

#ifndef ToolFunction_hpp
#define ToolFunction_hpp

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "ResourcesPath.h"

inline cocos2d::Menu *createMenuWithSpriteByThreeTextureAndCallback(const std::string &normalTexture, const std::string &selectedTexture, const std::string &disabledTexture, const cocos2d::ccMenuCallback &callback){
    
    cocos2d::Sprite *normalSprite;
    cocos2d::Sprite *selectedSprite;
    cocos2d::Sprite *disabledSprite;
    
    if (normalTexture.substr(0, 4) == "res/"){
        normalSprite = cocos2d::Sprite::create(normalTexture);
        selectedSprite = cocos2d::Sprite::create(selectedTexture);
        disabledSprite = cocos2d::Sprite::create(disabledTexture);
        
    }else {
        normalSprite = cocos2d::Sprite::createWithSpriteFrameName(normalTexture);
        selectedSprite = cocos2d::Sprite::createWithSpriteFrameName(selectedTexture);
        disabledSprite = cocos2d::Sprite::createWithSpriteFrameName(disabledTexture);
    }
    
    cocos2d::MenuItemSprite *itemSprite = cocos2d::MenuItemSprite::create(normalSprite, selectedSprite, disabledSprite, callback);
    cocos2d::Menu *menu = cocos2d::Menu::create(itemSprite, NULL);
    return menu;
    
}

inline cocos2d::Menu *createMenuWithImageByThreeTextureAndCallback(const std::string &normalTexture, const std::string &selectedTexture, const std::string &disabledTexture, const cocos2d::ccMenuCallback &callback){
    
    cocos2d::MenuItemImage *itemImage = cocos2d::MenuItemImage::create(normalTexture, selectedTexture, disabledTexture, callback);
    cocos2d::Menu *menu = cocos2d::Menu::create(itemImage, NULL);
    return menu;
    
}

inline void loadWorldMapSpriteSheet(){
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLDMAP_UI_PLIST);
}

inline void prepareWorldMap(){
    cocos2d::SpriteFrameCache::getInstance()->removeSpriteFrames();
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(WORLDMAP_UI_PLIST);
}

inline void prepareBattle(){
    cocos2d::SpriteFrameCache::getInstance()->removeSpriteFrames();
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(BATTLE_UI_PLIST);
}

inline void prepareMainMenu(){
    cocos2d::SpriteFrameCache::getInstance()->removeSpriteFrames();
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(MAINMENU_UI_PLIST);
}

inline void prepareCredits(){
    cocos2d::SpriteFrameCache::getInstance()->removeSpriteFrames();
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(CREDITS_UI_PLIST);
}

inline std::string int2string(int number){
    
    int numberToConver = number;
    int size = 0;
    do {
        ++size;
    }while (numberToConver /= 10);
    
    size *= 2;
    
    char str[size];
    int len = snprintf(str, sizeof(str), "%d", number);
    if (len > sizeof(str) - 1){
        std::cout << __func__ << "缓冲区溢出！！！！" << std::endl;
    }
    
    std::string string(str);
    return string;
}

inline int string2int(const std::string &string){
    int number;
    sscanf(string.c_str(), "%d", &number);
    return number;
}

inline std::string double2string(double number){
    char *str;
    sprintf(str, "%f", number);
    return std::string(str);
}

inline double string2double(const std::string &string){
    double number;
    sscanf(string.c_str(), "%lf", &number);
    return number;
}


#endif /* ToolFunction_hpp */
