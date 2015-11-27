//
//  GameData.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/14.
//
//

#ifndef GameData_hpp
#define GameData_hpp

#include <stdio.h>
#include "cocos2d.h"

#include "MonsterData.hpp"
#include "BattleData.hpp"
#include "TowerData.hpp"
#include "TowerActorData.hpp"
#include "TowerShooterData.hpp"
#include "TowerShootThingData.hpp"

/// 所有 Tower 和 Monster 的名字在这里，只是为了防止本人拙劣的低级的拼写错误
class MonsterName {
public:
    std::string desertThug = "desertThug";
    
};

class TowerName {
public:
    std::string archerTower    = "archer_tower";
    std::string defenceTower   = "defence_tower";
    std::string mageTower      = "mage_tower";
    std::string artilleryTower = "artillery_tower";
};

class TowerLevel {
public:
    std::string level1  = "level1";
    std::string level2  = "level2";
    std::string level3  = "level3";
    std::string level41 = "level41";
    std::string level42 = "level42";
};

class TowerShooterName {
public:
    std::string archer = "archer";
    std::string soldier = "soldier";
    std::string mage = "mage";
    std::string artillery = "artillery";
};

class TowerShootThingName {
public:
    std::string arrow = "arrow";
    std::string magic = "magic";
    std::string bomb  = "bomb";
};

class TowerLevelTag {
public:
    std::string level1  = "level1";
    std::string level2  = "level2";
    std::string level3  = "level3";
    std::string level41 = "level41";
    std::string level42 = "level42";
};
//防止拼写错误完了，呵呵

class GameData {
    
public:
    
    static GameData *getInstance();
    
    static const float defaultDelayPerUnit;
    
    //Monster
    std::map<std::string, MonsterData> monsterDataMap;
    static const MonsterName monsterName;
    void loadMonsterData();
    MonsterData getMonsterDataByMonsterName(const std::string &monsterName);
    
    //Battle
    std::map<std::string, BattleData> battleData;
    void loadBattleData();
    
    //Tower
    static const TowerName towerName;
    static const TowerLevelTag towerLevelTag;
    static const TowerShooterName towerShooterName;
    static const TowerShootThingName towerShootThingName;
    std::map<std::string, std::map<std::string, TowerData>> towerData;
    std::map<std::string, std::map<std::string, TowerActorData>> towerActorData;
    std::map<std::string, std::map<std::string, TowerShooterData>> towerShooterData;
    std::map<std::string, std::map<std::string, TowerShootThingData>> towerShootThingData;
    void loadTowerData();
    void loadTowerActorData();
    void loadTowerShooterData();
    void loadTowerShootThingData();
    //TODO: 11,24
    TowerData getTowerDataByTowerNameAndLevel(const std::string &name, const std::string &level);
    TowerActorData getTowerActorDataByNameAndLevel(const std::string &name, const std::string &level);
    TowerShooterData getTowerShooterDataByNameAndLevel(const std::string &name, const std::string &level);
    TowerShootThingData getTowerShootThingDataByNameAndLevel(const std::string &name, const std::string &level);
    
private:
    
    GameData() = default;
    ~GameData() = default;
    
    static GameData *_gameData;
};

#endif /* GameData_hpp */
