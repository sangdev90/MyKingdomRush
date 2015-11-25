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
const TowerName GameData::towerName{};
const TowerLevelTag GameData::towerLevelTag{};
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

#pragma mark - Load Methods

void GameData::loadMonsterData(){
    
    std::string monsterDataFullPath = FileUtils::getInstance()->fullPathForFilename(MONSTER_DATA_JSON);
    std::string monsterStringData = FileUtils::getInstance()->getStringFromFile(monsterDataFullPath);
//    CCLOG("%s", monsterStringData.c_str());
    
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

void GameData::loadTowerData(){
    std::string towerDataFileFullPath = FileUtils::getInstance()->fullPathForFilename(TOWER_DATA_JSON);
    std::string towerStringData = FileUtils::getInstance()->getStringFromFile(towerDataFileFullPath);
    
    std::vector<std::string> towerNameVector = {"archer_tower", "defence_tower", "mage_tower", "artillery_tower"};
    std::vector<std::string> towerLevelTagVector = {"level1", "level2", "level3", "level41", "level42"};
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(towerStringData.c_str());
    if (jsonDocument.HasParseError()){
        CCLOG("Parse Tower Data Error %d", jsonDocument.GetParseError());
        return;
    }
    for (std::string towerNameString : towerNameVector){
        
        std::map<std::string, TowerData> oneTowerData;
        if (jsonDocument[towerNameString.c_str()].IsObject()){
            for (std::string towerLevelTagString : towerLevelTagVector){
                
                if (jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()].IsObject()){
                    
                    TowerData towerDataItem;
                    
                    towerDataItem.attackTime = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackTime"].GetString();
                    towerDataItem.scope = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["scope"].GetString();
                    towerDataItem.soldierOutTowerNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["soldierOutTowerNumber"].GetInt();
                    //TODO: Soldier Name To Be Done
//                    towerDataItem.soldierOutTowerName = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["soldierOutTowerName"].GetString();
                    
                    oneTowerData[towerLevelTagString] = towerDataItem;
                    
                }
            }
        }
        
        towerData[towerNameString] = oneTowerData;
        
    }
    
//    CCLOG("STL 中的 TowerData --------------------------------------------------------------------------------");
//    for (std::pair<std::string, std::map<std::string, TowerData>> iterOutside : towerData){
//        CCLOG("%s", iterOutside.first.c_str());
//        for (std::pair<std::string, TowerData> iterInSide : iterOutside.second){
//            CCLOG("%s", iterInSide.first.c_str());
//            TowerData &printTowerData = iterInSide.second;
//            CCLOG("AttackTime : %s", printTowerData.attackTime.c_str());
//            CCLOG("Scope : %s", printTowerData.scope.c_str());
//            CCLOG("SoldierOutTowerName : %s", printTowerData.soldierOutTowerName.c_str());
//            CCLOG("SoldierOutTowerNumber : %d", printTowerData.soldierOutTowerNumber);
//        }
//    }
//    
////    CCLOG("另一种输出方法：");
////    for (auto name : towerNameVector){
////        for (auto level : towerLevelTagVector){
////            TowerData printTowerData = this->getTowerDataByTowerNameAndLevel(name, level);
////            CCLOG("AttackTime : %s", printTowerData.attackTime.c_str());
////            CCLOG("Scope : %s", printTowerData.scope.c_str());
////            CCLOG("SoldierOutTowerName : %s", printTowerData.soldierOutTowerName.c_str());
////            CCLOG("SoldierOutTowerNumber : %d", printTowerData.soldierOutTowerNumber);
////        }
////    }
//    CCLOG("--------------------------------------------------------------------------------------------------");
    
}

void GameData::loadTowerActorData(){
    
    std::string towerActorDataFileFullPath = FileUtils::getInstance()->fullPathForFilename(TOWER_ACTOR_DATA_JSON);
    std::string towerActorDataString = FileUtils::getInstance()->getStringFromFile(towerActorDataFileFullPath);
    
    std::vector<std::string> towerNameVector = {"archer_tower", "defence_tower", "mage_tower", "artillery_tower"};
    std::vector<std::string> towerLevelTagVector = {"level1", "level2", "level3", "level41", "level42"};
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(towerActorDataString.c_str());
    if (jsonDocument.HasParseError()){
        CCLOG("Parse TowerActorData Error : %d", jsonDocument.GetParseError());
        return;
    }
    
    for (std::string towerNameString : towerNameVector){
        
        std::map<std::string, TowerActorData> oneTowerData;
        
        for (std::string towerLevelTagString : towerLevelTagVector){
            
            TowerActorData towerActorDataItem;
            
            towerActorDataItem.shooterName = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["shooterName"].GetString();
            towerActorDataItem.shootThing = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["shootThing"].GetString();
            towerActorDataItem.attackFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackFrameNumber"].GetInt();
            
            towerActorDataItem.attackEffectFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackEffectFrameNumber"].GetInt();
            towerActorDataItem.dispatchSoldierFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["dispatchSoldierFrameNumber"].GetInt();
            towerActorDataItem.attackBaseFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackBaseFrameNumber"].GetInt();
            towerActorDataItem.attackTopFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackTopFrameNumber"].GetInt();
            towerActorDataItem.attackSmokeFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackSmokeFrameNumber"].GetInt();
            towerActorDataItem.attackReloadFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackReloadFrameNumber"].GetInt();
            towerActorDataItem.attackArtilleryLeftFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackArtilleryLeftFrameNumber"].GetInt();
            towerActorDataItem.attackArtilleryRightFrameNumber = jsonDocument[towerNameString.c_str()][towerLevelTagString.c_str()]["attackArtilleryRightFrameNumber"].GetInt();
            
            oneTowerData[towerLevelTagString] = towerActorDataItem;
        }
        
        towerActorData[towerNameString] = oneTowerData;
    }
    
//    CCLOG("STL 中的 TowerActorData --------------------------------------------------------------------------------");
//    
//    for (auto nameString : towerNameVector){
//        for (auto levelString : towerLevelTagVector){
//            
//            CCLOG("Shooter Name : %s", towerActorData[nameString][levelString].shooterName.c_str());
//            CCLOG("Shoot Thing : %s", towerActorData[nameString][levelString].shootThing.c_str());
//            CCLOG("Attack Frame Number : %d", towerActorData[nameString][levelString].attackFrameNumber);
//            CCLOG("Attack Effect Frame Number : %d", towerActorData[nameString][levelString].attackEffectFrameNumber);
//            CCLOG("Dispatch Soldier Frame Number : %d", towerActorData[nameString][levelString].dispatchSoldierFrameNumber);
//            CCLOG("Attack Base Frame Number : %d", towerActorData[nameString][levelString].attackBaseFrameNumber);
//            CCLOG("Attack Top Frame Number : %d", towerActorData[nameString][levelString].attackTopFrameNumber);
//            CCLOG("Attack Smoke Frame Number : %d", towerActorData[nameString][levelString].attackSmokeFrameNumber);
//            CCLOG("Attack Reload Frame Number : %d", towerActorData[nameString][levelString].attackReloadFrameNumber);
//            CCLOG("Attack Artillery Left Frame Number : %d", towerActorData[nameString][levelString].attackArtilleryLeftFrameNumber);
//            CCLOG("Attack Artillery Right Frame Number : %d", towerActorData[nameString][levelString].attackArtilleryRightFrameNumber);
//            
//        }
//    }
//    
//    CCLOG("--------------------------------------------------------------------------------------------------------");
    
}

void GameData::loadTowerShooterData(){
    std::string towerShooterDataFileFullPath = FileUtils::getInstance()->fullPathForFilename(TOWER_SHOOTER_DATA_JSON);
    std::string towerShooterDataString = FileUtils::getInstance()->getStringFromFile(towerShooterDataFileFullPath);
    
    std::vector<std::string> towerShooterNameVector = {"archer", "soldier", "mage", "artillery"};
    std::vector<std::string> towerLevelTagVector = {"level1", "level2", "level3", "level41", "level42"};
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(towerShooterDataString.c_str());
    if (jsonDocument.HasParseError()){
        CCLOG("Parse TowerShooterData Error : %d", jsonDocument.GetParseError());
        return;
    }
    
    for (std::string towerShooterNameString : towerShooterNameVector){
        
        std::map<std::string, TowerShooterData> oneTowerData;
        
        for (std::string towerLevelTagString : towerLevelTagVector){
            
            TowerShooterData towerShooterDataitem;
            
            towerShooterDataitem.preAttackDownFrameNumber = jsonDocument[towerShooterNameString.c_str()][towerLevelTagString.c_str()]["preAttackDownFrameNumber"].GetInt();
            towerShooterDataitem.postAttackDownFrameNumber = jsonDocument[towerShooterNameString.c_str()][towerLevelTagString.c_str()]["postAttackDownFrameNumber"].GetInt();
            towerShooterDataitem.preAttackUpFrameNumber = jsonDocument[towerShooterNameString.c_str()][towerLevelTagString.c_str()]["preAttackUpFrameNumber"].GetInt();
            towerShooterDataitem.postAttackUpFrameNumber = jsonDocument[towerShooterNameString.c_str()][towerLevelTagString.c_str()]["postAttackUpFrameNumber"].GetInt();
            
            oneTowerData[towerLevelTagString] = towerShooterDataitem;
        }
        
        towerShooterData[towerShooterNameString] = oneTowerData;
        
    }
    
//    CCLOG("STL 中的 TowerShooterData --------------------------------------------------------------------------------");
//    
//    for (auto nameString : towerShooterNameVector){
//        for (auto levelString : towerLevelTagVector){
//            
//            CCLOG("PreAttack Up Frame Number %d", towerShooterData[nameString][levelString].preAttackUpFrameNumber);
//            CCLOG("PostAttack Up Frame Number %d", towerShooterData[nameString][levelString].postAttackUpFrameNumber);
//            CCLOG("PreAttack Down Frame Number %d", towerShooterData[nameString][levelString].preAttackDownFrameNumber);
//            CCLOG("PostAttack Down Frame Number %d", towerShooterData[nameString][levelString].postAttackDownFrameNumber);
//            
//        }
//    }
//    
//    CCLOG("----------------------------------------------------------------------------------------------------------");
}

void GameData::loadTowerShootThingData(){
    std::string towerShootThingDataFileFullPath = FileUtils::getInstance()->fullPathForFilename(TOWER_SHOOT_THING_DATA_JSON);
    std::string towerShootThingDataString = FileUtils::getInstance()->getStringFromFile(towerShootThingDataFileFullPath);
    
    std::vector<std::string> towerShootThingNameVector = {"arrow", "magic", "bomb"};
    std::vector<std::string> towerLevelTagVector = {"level1", "level2", "level3", "level41", "level42"};
    
    rapidjson::Document jsonDocument;
    jsonDocument.Parse<0>(towerShootThingDataString.c_str());
    if (jsonDocument.HasParseError()){
        CCLOG("Parse TowerShootThing Error : %d", jsonDocument.GetParseError());
        return;
    }
    
    for (std::string towerShootThingNameString : towerShootThingNameVector){
        
        std::map<std::string, TowerShootThingData> oneThingData;
        
        for (std::string towerLevelTagString : towerLevelTagVector){
            
            TowerShootThingData towerShootThingDataItem;
            
            towerShootThingDataItem.name = jsonDocument[towerShootThingNameString.c_str()][towerLevelTagString.c_str()]["name"].GetString();
            towerShootThingDataItem.level = jsonDocument[towerShootThingNameString.c_str()][towerLevelTagString.c_str()]["level"].GetString();
            towerShootThingDataItem.physicalProperty = jsonDocument[towerShootThingNameString.c_str()][towerLevelTagString.c_str()]["physicalProperty"].GetInt();
            towerShootThingDataItem.magicProperty = jsonDocument[towerShootThingNameString.c_str()][towerLevelTagString.c_str()]["magicProperty"].GetInt();
            
            
            oneThingData[towerLevelTagString] = towerShootThingDataItem;
        }
        
        towerShootThingData[towerShootThingNameString] = oneThingData;
        
    }
    
//    CCLOG("STL 中的 TowerShootThingData --------------------------------------------------------------------------------");
//    
//    for (auto nameString : towerShootThingNameVector){
//        for (auto levelString : towerLevelTagVector){
//            
//            CCLOG("Name : %s", towerShootThingData[nameString][levelString].name.c_str());
//            CCLOG("Level : %s", towerShootThingData[nameString][levelString].level.c_str());
//            CCLOG("Physical Property : %d", towerShootThingData[nameString][levelString].physicalProperty);
//            CCLOG("Magic Property : %d", towerShootThingData[nameString][levelString].magicProperty);
//            
//        }
//    }
//    
//    CCLOG("-------------------------------------------------------------------------------------------------------------");
    
}


#pragma mark - Get Methods

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

TowerData GameData::getTowerDataByTowerNameAndLevel(const std::string &name, const std::string &level){
    
    if (towerData.find(name) == towerData.end()){
        TowerData getTowerData;
        CCLOG("GameData %s, Can't find Tower Data for name : %s", __func__, name.c_str());
        return getTowerData;
    }else {
        if (towerData.find(name)->second.find(level) == towerData.find(name)->second.end()){
            TowerData getTowerData;
            CCLOG("GameData %s, Can't find Tower Data for name : %s, level : %s", __func__, name.c_str(), level.c_str());
            return getTowerData;
        }else {
            TowerData getTowerData = towerData[name][level];
            return getTowerData;
        }
    }
}

TowerActorData GameData::getTowerActorDataByNameAndLevel(const std::string &name, const std::string &level){
    
    if (towerActorData.find(name) == towerActorData.end()){
        TowerActorData getTowerActorData;
        CCLOG("GameData %s, Can't find Tower Actor Data for name : %s", __func__, name.c_str());
        return getTowerActorData;
    } else if (towerActorData.find(name)->second.find(level) == towerActorData.find(name)->second.end()){
        TowerActorData getTowerActorData;
        CCLOG("GameData %s, Can't find Tower Data for name : %s, for level : %s", __func__, name.c_str(), level.c_str());
        return getTowerActorData;
    }else {
        TowerActorData getTowerActorData = towerActorData[name][level];
        return getTowerActorData;
    }
}

TowerShooterData GameData::getTowerShooterDataByNameAndLevel(const std::string &name, const std::string &level){
    if (towerShooterData.find(name) == towerShooterData.end()){
        TowerShooterData getTowershooterData;
        CCLOG("GameData %s, Can't find Tower Shooter Data for name : %s", __func__, name.c_str());
        return getTowershooterData;
    }else if (towerShooterData.find(name)->second.find(level) == towerShooterData.find(name)->second.end()){
        TowerShooterData getTowerShooterData;
        CCLOG("GameData %s, Can't find Tower Shooter data for name : %s, for level : %s", __func__, name.c_str(), level.c_str());
        return getTowerShooterData;
    }else {
        TowerShooterData getTowerShooterData = towerShooterData[name][level];
        return getTowerShooterData;
    }
}

TowerShootThingData GameData::getTowerShootThingDataByNameAndLevel(const std::string &name, const std::string &level){
    if (towerShootThingData.find(name) == towerShootThingData.end()){
        TowerShootThingData getTowerShootThingData;
        CCLOG("GameData %s, Can't find Tower Shooter Thing Data for name : %s", __func__, name.c_str());
        return getTowerShootThingData;
    }else if (towerShootThingData.find(name)->second.find(level) == towerShootThingData.find(name)->second.end()){
        TowerShootThingData getTowerShootThingData;
        CCLOG("GameData %s, Can't find Tower Shooter Thing Data for name : %s, for level : %s", __func__, name.c_str(), level.c_str());
        return getTowerShootThingData;
    }else {
        TowerShootThingData getTowerShooterThingData = towerShootThingData[name][level];
        return getTowerShooterThingData;
    }
}


