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

class GameData {
    
public:
    
    static GameData *getInstance();
    
    
    std::map<std::string, MonsterData> monsterData;
    void loadMonsterData();
    
    std::map<std::string, BattleData> battleData;
    void loadBattleData();
    
    
    
private:
    
    GameData() = default;
    ~GameData() = default;
    
    static GameData *_gameData;
    
    
    
    
};

#endif /* GameData_hpp */
