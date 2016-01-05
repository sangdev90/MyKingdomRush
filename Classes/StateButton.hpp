//
//  StateButton.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 16/1/2.
//
//

#ifndef StateButton_hpp
#define StateButton_hpp

#include <stdio.h>
#include "cocos2d.h"

enum {
    StateButtonOn = 0,
    StateButtonOff
};

class StateButton : public cocos2d::Sprite {
public:
    
    static StateButton *createStateButton(const std::string &iconSpriteFrameName, const std::string &offIconSpriteFrameName);
    
    void setChangeToOnCallback(const std::function<void ()> &callback);
    void setChangeToOffCallback(const std::function<void ()> &callback);
    
    void changeState();
    void setState(int state);
    
    virtual void onEnter();
    virtual void onExit();
    virtual bool initWithTwoSpriteFrameName(const std::string &iconSpriteFrameName, const std::string &offIconSpriteFrameName);
    
private:
    
    std::function<void ()> _changeToOnCallback = [](){
        CCLOG("Default ChangeToOnCallback. Please Set!");
    };
    std::function<void ()> _changeToOffCallback = [](){
        CCLOG("Default ChangeToOffCallback. Please Set!");
    };
    
    int _state = StateButtonOff;
    bool _touchBegan = false;
    cocos2d::EventListenerTouchOneByOne *_touchListener;
    cocos2d::Sprite *_offIcon;
    
    void _addTouchListener();
    
};

#endif /* StateButton_hpp */
