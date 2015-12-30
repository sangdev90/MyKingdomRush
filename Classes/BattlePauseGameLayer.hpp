//
//  BattlePauseGameLayer.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/12/29.
//
//

#ifndef BattlePauseGameLayer_hpp
#define BattlePauseGameLayer_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class BattlePauseGameLayer : public cocos2d::Layer{
public:
    
    static BattlePauseGameLayer *createBattlePauseGameLayer();
    
    void show(const std::function<void ()> &callback);
    void close(const std::function<void ()> &callback);
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    
private:
    
    cocos2d::LayerColor *_grayBackgroundLayer;
    cocos2d::Layer *_backgroundLayer;
    cocos2d::MenuItemImage *_restartMenuItem;
    cocos2d::MenuItemImage *_quitMenuItem;
    cocos2d::Sprite *_musicIcon;
    cocos2d::Sprite *_soundIcon;
    cocos2d::Sprite *_vibrateIcon;
    cocos2d::ui::Button *closeButton;
    
    cocos2d::EventListenerTouchOneByOne *_swallowTouchListener;
    
    void _layoutUI();
    void _addSwallowTouchListener();
    void _removeSwallowtouchListener();
    
};

#endif /* BattlePauseGameLayer_hpp */
