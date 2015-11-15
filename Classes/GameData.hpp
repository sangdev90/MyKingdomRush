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

/// 所有 Monster 的名字在这里，只是为了防止本人拙劣的低级的拼写错误
class MonsterName {
public:
    std::string desertThug = "desertThug";
    
};

class GameData {
    
public:
    
    static GameData *getInstance();
    
    
    std::map<std::string, MonsterData> monsterDataMap;
    static const MonsterName monsterName;
    void loadMonsterData();
    MonsterData getMonsterDataByMonsterName(const std::string &monsterName);
    
    std::map<std::string, BattleData> battleData;
    void loadBattleData();
    
    
    
    
private:
    
    GameData() = default;
    ~GameData() = default;
    
    static GameData *_gameData;
    
    
    
    
};

#endif /* GameData_hpp */
