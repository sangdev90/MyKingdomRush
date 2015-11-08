//
//  MainMenu.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/10/30.
//
//

#ifndef MainMenu_hpp
#define MainMenu_hpp

#include <stdio.h>
#include "cocos2d.h"

class MainMenu : public cocos2d::Layer{
public:
    
    MainMenu(bool is)
    : isGameStart(is) {};
    
    static cocos2d::Scene *createScene(bool is);
    static MainMenu *create(bool is);
    
    virtual bool init();
    virtual void onEnter();
    
    
private:
    cocos2d::Size visibleSize;
    bool isGameStart;
};

#endif /* MainMenu_hpp */
