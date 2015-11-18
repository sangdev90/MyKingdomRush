//
//  GameData.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#include "GameData.hpp"
#include "ToolFunction.hpp"
#include "ResourcesPath.h"

#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/document.h"

USING_NS_CC;

GameData *GameData::_gameData = nullptr;
const MonsterName GameData::monsterName{};
const float GameData::defaultDelayPerUnit = 0.05;

GameData *GameData::getInstance(){
    if (_gameData == nullptr){
        CCLOG("New GameData , 如果重复输出，有多线程问题");
        _gameData = new (std::nothrow) GameData();
        if (_gameData){
            return _gameData;
        }else {
            CCLOG("Game Data Construct Fail!!!");
            delete _gameData;
            _gameData = nullptr;
            return nullptr;
        }
    }
    return _gameData;
}

void GameData::loadMonsterData(){
    
    std::string monsterDataFullPath = FileUtils::getInstance()->fullPathForFilename(MONSTER_DATA_JSON);
    std::string monsterStringData = FileUtils::getInstance()->getStringFromFile(monsterDataFullPath);
    CCLOG("%s", monsterStringData.c_str());
    
    rapidjson::Document jsonDocoment;
    jsonDocoment.Parse<0>(monsterStringData.c_str());
    if (jsonDocoment.HasParseError()){
        CCLOG("Parse MonsterData Error %d", jsonDocoment.GetParseError());
        return;
    }
    
    if (jsonDocoment.IsObject()){
        for (auto iter = jsonDocoment.MemberBegin(); iter != jsonDocoment.MemberEnd(); ++iter){
            std::string monsterNameKey = iter->name.GetString();
            CCLOG("%s", monsterNameKey.c_str());
            
            MonsterData monsterData{};
            monsterData.id = iter->value["id"].GetInt();
            monsterData.name = iter->value["name"].GetString();
            monsterData.numberOfAttackFrame = iter->value["numberOfAttackFrame"].GetInt();
            monsterData.numberOfBcakwardFrame = iter->value["numberOfBackwardFrame"].GetInt();
            monsterData.numberOfDieFrame = iter->value["numberOfDieFrame"].GetInt();
            monsterData.numberOfForwardFrame = iter->value["numberOfForwardFrame"].GetInt();
            monsterData.numberOfTowardFrame = iter->value["numberOfTowardFrame"].GetInt();
            monsterData.hp = iter->value["HP"].GetInt();
            monsterData.speed = iter->value["Speed"].GetInt();
            monsterDataMap[monsterNameKey] = monsterData;
        }
        
    }
    
    
    CCLOG("STL 中的 MonsterData:");
    for (std::pair<std::string, MonsterData> monsterDataPair : monsterDataMap){
        CCLOG("%s :", monsterDataPair.first.c_str());
        MonsterData *monsterDataItem = static_cast<MonsterData *>(&monsterDataPair.second);
        CCLOG("name: %s", monsterDataItem->name.c_str());
        CCLOG("id: %d", monsterDataItem->id);
        CCLOG("frameInfo: %d, %d, %d, %d, %d", monsterDataItem->numberOfAttackFrame, monsterDataItem->numberOfBcakwardFrame, monsterDataItem->numberOfDieFrame, monsterDataItem->numberOfForwardFrame, monsterDataItem->numberOfTowardFrame);
        CCLOG("HP: %d", monsterDataItem->hp);
        CCLOG("Speed: %d", monsterDataItem->speed);
    }
    
}

MonsterData GameData::getMonsterDataByMonsterName(const std::string &monsterName){
    if (monsterDataMap.size() == 0){
        CCLOG("Monster is not init!!!!");
        MonsterData monsterData{};
        return monsterData;
    }
    
    if (monsterDataMap.find(monsterName) != monsterDataMap.end()){
        MonsterData monsterData = monsterDataMap[monsterName];
        return monsterData;
    }else {
        CCLOG("Can't find monsterData %s", monsterName.c_str());
        MonsterData monsterData{};
        return monsterData;

    }
}
