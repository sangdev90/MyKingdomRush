//
//  BattlePersonInfoBoardSprite.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/27.
//
//

#ifndef BattlePersonInfoBoardSprite_hpp
#define BattlePersonInfoBoardSprite_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "UsefulDataStructure.h"

enum {
    battle_person_info_board_state_monster = 0,
    battle_person_info_board_state_tower,
    battle_person_info_board_state_hero,
    battle_person_info_board_state_boss,
    battle_person_info_board_state_power
};

class BattlePersonInfoBoardSprite : public cocos2d::Sprite{
public:
    
    static BattlePersonInfoBoardSprite *createBattlePersonInfoBoardSpriteWithMonsterData(const BattleMonsterInfoData &infoData);
    static BattlePersonInfoBoardSprite *createBattlePersonInfoBoardSpriteWithTowerData(const BattleTowerInfoData &infoData);
    static BattlePersonInfoBoardSprite *createBattlePersonInfoBoardSpriteWithHeroData(const BattleHeroInfoData &infoData);
    static BattlePersonInfoBoardSprite *createBattlePersonInfoBoardSpriteWithBossData(const BattleBossInfoData &infoData);
    static BattlePersonInfoBoardSprite *createBattlePersonInfoBoardSpriteWithPowerData(const BattlePowerInfoData &infoData);
    
    BattlePersonInfoBoardSprite(const BattleMonsterInfoData &infoData): _monsterInfoData(infoData) { _state = battle_person_info_board_state_monster; }
    BattlePersonInfoBoardSprite(const BattleTowerInfoData &infoData)  : _towerInfoData(infoData) { _state = battle_person_info_board_state_tower; }
    BattlePersonInfoBoardSprite(const BattleHeroInfoData &infoData)   : _heroInfoData(infoData) { _state = battle_person_info_board_state_hero; }
    BattlePersonInfoBoardSprite(const BattleBossInfoData &infoData)   : _bossInfoData(infoData) { _state = battle_person_info_board_state_boss; }
    BattlePersonInfoBoardSprite(const BattlePowerInfoData &infoData)  : _powerInfoData(infoData) { _state = battle_person_info_board_state_power; }
    
    virtual bool init();
    
private:
    
    int _state = 0;
    
    BattleMonsterInfoData _monsterInfoData;
    BattleTowerInfoData _towerInfoData;
    BattleHeroInfoData _heroInfoData;
    BattleBossInfoData _bossInfoData;
    BattlePowerInfoData _powerInfoData;
    
    void _layout();
    
};

#endif /* BattlePersonInfoBoardSprite_hpp */
