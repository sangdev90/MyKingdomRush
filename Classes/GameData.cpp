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
    
    
    
}
