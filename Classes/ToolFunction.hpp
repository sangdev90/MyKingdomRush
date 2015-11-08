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


#endif /* ToolFunction_hpp */
