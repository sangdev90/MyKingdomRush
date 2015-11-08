//
//  BattleDisplayBoardSprite.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#ifndef BattleDisplayBoardSprite_hpp
#define BattleDisplayBoardSprite_hpp

#include <stdio.h>
#include "cocos2d.h"

class BattleDisplayBoardSprite : public cocos2d::Sprite{
public:
    
    BattleDisplayBoardSprite(int numberOfHP = 0, int numberOfCoin = 0, int numberOfWave = 0, int numberOfTotalWave = 0)
    : _numberOfHP(numberOfHP), _numberOfCoin(numberOfCoin), _numberOfWave(numberOfWave), _numberOfTotalWave(numberOfTotalWave) {};
    
    static BattleDisplayBoardSprite *createWithInformationAndSpriteFrameName(int numberOfHP, int numberOfCoin, int numberOfWave, int numberOfTotalWave, const std::string &spriteFrameName);
    
    virtual void onEnter();
    
    void updateHP(int numberOfHP);
    void updateCoin(int numberOfCoin);
    void updateWave(int numberOfWave);
    
private:
    
    int _numberOfHP;
    int _numberOfCoin;
    int _numberOfWave;
    int _numberOfTotalWave;
    
    cocos2d::Label *_labelOfHP;
    cocos2d::Label *_labelOfCoin;
    cocos2d::Label *_labelOfWave;
};

#endif /* BattleDisplayBoardSprite_hpp */
