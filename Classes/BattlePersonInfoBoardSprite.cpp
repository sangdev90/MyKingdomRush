//
//  BattlePersonInfoBoardSprite.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/27.
//
//

#include "BattlePersonInfoBoardSprite.hpp"

#pragma mark - Static Method

BattlePersonInfoBoardSprite *BattlePersonInfoBoardSprite::createBattlePersonInfoBoardSpriteWithMonsterData(const BattleMonsterInfoData &infoData){
    BattlePersonInfoBoardSprite *board = new (std::nothrow) BattlePersonInfoBoardSprite(infoData);
    if (board && board->init()){
        board->autorelease();
        return board;
    }
    
    delete board;
    board = nullptr;
    return nullptr;
}

BattlePersonInfoBoardSprite *BattlePersonInfoBoardSprite::createBattlePersonInfoBoardSpriteWithTowerData(const BattleTowerInfoData &infoData){
    BattlePersonInfoBoardSprite *board = new (std::nothrow) BattlePersonInfoBoardSprite(infoData);
    if (board && board->init()){
        board->autorelease();
        return board;
    }
    
    delete board;
    board = nullptr;
    return nullptr;
}

BattlePersonInfoBoardSprite *BattlePersonInfoBoardSprite::createBattlePersonInfoBoardSpriteWithHeroData(const BattleHeroInfoData &infoData){
    BattlePersonInfoBoardSprite *board = new (std::nothrow) BattlePersonInfoBoardSprite(infoData);
    if (board && board->init()){
        board->autorelease();
        return board;
    }
    
    delete board;
    board = nullptr;
    return board;
}

BattlePersonInfoBoardSprite *BattlePersonInfoBoardSprite::createBattlePersonInfoBoardSpriteWithBossData(const BattleBossInfoData &infoData){
    BattlePersonInfoBoardSprite *board = new (std::nothrow) BattlePersonInfoBoardSprite(infoData);
    if (board && board->init()){
        board->autorelease();
        return board;
    }
    
    delete board;
    board = nullptr;
    return nullptr;
}

BattlePersonInfoBoardSprite *BattlePersonInfoBoardSprite::createBattlePersonInfoBoardSpriteWithPowerData(const BattlePowerInfoData &infoData){
    BattlePersonInfoBoardSprite *board = new (std::nothrow) BattlePersonInfoBoardSprite(infoData);
    if (board && board->init()){
        board->autorelease();
        return board;
    }
    
    delete board;
    board = nullptr;
    return nullptr;
}

#pragma mark - Other Method

bool BattlePersonInfoBoardSprite::init(){
    if (!initWithSpriteFrameName("battle_ui_person_info_background.png")){
        return false;
    }
    
    return true;
}

void BattlePersonInfoBoardSprite::_layout(){
    switch (_state){
        case battle_person_info_board_state_monster:{
            break;
        }
            
        case battle_person_info_board_state_boss:{
            break;
        }
            
        case battle_person_info_board_state_hero:{
            break;
        }
            
        case battle_person_info_board_state_power:{
            break;
        }
            
        case battle_person_info_board_state_tower:{
            break;
        }
            
        default:{
            break;
        }
    }
}