//
//  BattleUILayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#ifndef BattleUILayer_hpp
#define BattleUILayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class BattleDisplayBoardSprite;
class BattlePauseGameLayer;

class BattleUILayer : public cocos2d::Layer{
public:
    
    static BattleUILayer *create();
    
    virtual bool init();
    
private:
    
    BattleDisplayBoardSprite *_displayBoardSprite;
    BattlePauseGameLayer *_pauseGameLayer;
    
    cocos2d::ui::Button *_pauseGameButton;
    
    void _layoutUI();
    void _pauseButtonTouchListener(Ref *sender, cocos2d::ui::Widget::TouchEventType touchType);
    
    void _someTestCode();
};

#endif /* BattleUILayer_hpp */
