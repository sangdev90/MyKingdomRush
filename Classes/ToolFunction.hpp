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
#include <math.h>
#include "cocos2d.h"
#include "ResourcesPath.h"
#include "BattleData.hpp"
#include "MonsterData.hpp"

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

/**
 *  一个比较安全的 int 转 std::string 函数
 *
 *  @param number 要转换的 int
 *
 *  @return 返回一个转换之后的 std::string
 */
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

/**
 *  std::string 转 int
 *
 *  @param string 要转换的 std::string
 *
 *  @return 转换之后的 int
 */
inline int string2int(const std::string &string){
    int number;
    sscanf(string.c_str(), "%d", &number);
    return number;
}

/**
 *  待修改
 *
 *  @param number <#number description#>
 *
 *  @return <#return value description#>
 */
inline std::string double2string(double number){
    char *str;
    sprintf(str, "%f", number);
    return std::string(str);
}

/**
 *  std::string 转 double
 *
 *  @param string 要转换的 std::string
 *
 *  @return 转换之后的 double
 */
inline double string2double(const std::string &string){
    double number;
    sscanf(string.c_str(), "%lf", &number);
    return number;
}

inline float distanceBetweenTwoVec2(const cocos2d::Vec2 &leftPoint, const cocos2d::Vec2 &rightPoint){
    return static_cast<float>(sqrt( (leftPoint.x - rightPoint.x)*(leftPoint.x - rightPoint.x) + (leftPoint.y - rightPoint.y)*(leftPoint.y - rightPoint.y) ));
}

/**
 *  打印 BattleData
 *
 *  @param battleData BattleData
 */
inline void printBattleData(const BattleData &battleData){
    CCLOG("游戏运行时的战场数据：---------------------------------------------------------------------");
    CCLOG("MonsterAppearPoint : (%f, %f)", battleData.monsterAppearPoint.x, battleData.monsterAppearPoint.y);
    CCLOG("DefencePoint: (%f, %f)", battleData.defencePoint.x, battleData.defencePoint.y);
    CCLOG("TowerBuildPoint:");
    CCLOG("Coin: %d", battleData.coin);
    CCLOG("HP: %d", battleData.hp);
    CCLOG("---------------------------------------------------------------------------------------");
}

/**
 *  打印 MonsterData
 *
 *  @param monsterData MonsterData
 */
inline void printMonsterData(const MonsterData &monsterData){
    CCLOG("Monster 数据：--------------------------------------------------------------------------");
    CCLOG("name: %s", monsterData.name.c_str());
    CCLOG("id: %d", monsterData.id);
    CCLOG("numberOfAttackFrame: %d", monsterData.numberOfAttackFrame);
    CCLOG("numberOfDieFrame: %d", monsterData.numberOfDieFrame);
    CCLOG("numberOfForwardFrame: %d", monsterData.numberOfForwardFrame);
    CCLOG("numberOfTowardFrame: %d", monsterData.numberOfTowardFrame);
    CCLOG("numberOfBcakwardFrame: %d", monsterData.numberOfBcakwardFrame);
    CCLOG("hp: %d", monsterData.hp);
    CCLOG("speed: %d", monsterData.speed);
    CCLOG("---------------------------------------------------------------------------------------");
}

/**
 *  获取 Monster 动画帧文件名
 *
 *  @param monsterName    Monster 名字
 *  @param animationName  动画种类名字
 *  @param animationOrder 第几帧
 *
 *  @return 动画帧文件名
 */
inline std::string getMonsterAnimationFrameName(const std::string &monsterName, const std::string &animationName, int animationOrder){
    
    std::string animationOrderString = "0";
    if (animationOrder < 10){
        animationOrderString += int2string(animationOrder);
    }else {
        animationOrderString = int2string(animationOrder);
    }
    
    std::string monsterAnimationFrameName = std::string("monster_animation_") + monsterName + "_" + animationName + "_" + animationOrderString + ".png";
//    CCLOG("%s, %s", __func__, monsterAnimationFrameName.c_str());
    return monsterAnimationFrameName;
    
}

/**
 *  获取 Monster 精灵帧 plist 文件路径
 *
 *  @param monsterName Monster 名字
 *
 *  @return plist 文件路径
 */
inline std::string getMonsterSpriteSheetPlistPath(const std::string &monsterName){
    //TODO: 这里可以加入一个在数据里查找怪物名字的处理，如果没有这个名字的怪物，那就不要再返回那个不存在的文件的路径了。等所有怪物的名字都有了再做这里吧！
    std::string spriteSheetPath = std::string("res/image/battle/spritesheet/monster_animation_") + monsterName + ".plist";
//    CCLOG("%s, %s", __func__, spriteSheetPath.c_str());
    return spriteSheetPath;
}

/**
 *  通过战场名获得 AStar plist 文件路径
 *
 *  @param stage 战场名
 *
 *  @return plist 文件路径
 */
inline std::string getBattleMapAstarDataPlistFilePathWithStageName(const std::string &stage){
    std::string battleMapPlistFilePath = "res/data/battle/";
    battleMapPlistFilePath += stage;
    battleMapPlistFilePath += "_astar.plist";
    CCLOG("%s : %s", __func__, battleMapPlistFilePath.c_str());
    return battleMapPlistFilePath;
}

/**
 *  通过战场名获得 Path plist 文件路径
 *
 *  @param stage 战场名
 *
 *  @return plist 文件路径
 */
inline std::string getBattleMapPathDataPlistFilePathWithStageName(const std::string &stage){
    std::string battleMapPlistFilePath = "res/data/battle";
    battleMapPlistFilePath += stage;
    battleMapPlistFilePath += "_paths.plist";
    CCLOG("%s : %s", __func__, battleMapPlistFilePath.c_str());
    return battleMapPlistFilePath;
}

#endif /* ToolFunction_hpp */
