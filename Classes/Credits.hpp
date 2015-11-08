//
//  Credits.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/2.
//
//

#ifndef Credits_hpp
#define Credits_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class CreditsData {
public:
    
    CreditsData(const std::string &creditsTitle, const std::vector<std::string> &creditsNames)
    : title(creditsTitle), names(creditsNames) {};
    
    std::string title;
    std::vector<std::string> names;
};

class Credits : public cocos2d::Layer{
public:
    static cocos2d::Scene *createScene();
    static Credits *create();
    
    virtual bool init();
    virtual void onEnter();
    virtual void onExit();
    virtual void update(float dt);
    
    void calculateScrollViewHeight();
    void parseCreditsData();
    void layout();
    
private:
    cocos2d::ui::ScrollView *scrollView;
    cocos2d::Sprite *studioLogo;
    cocos2d::Sprite *cocosLogo;
    cocos2d::Sprite *swordIcon;
    cocos2d::Menu *backButton;
    std::vector<CreditsData> creditData;
    cocos2d::Sprite *backgroundTop;
    cocos2d::Sprite *backgroundButtom;
    
    float scrollViewHeight = 0;
    int theNumberOfBackground;
    int titleSize = 30;
    int nameSize = 20;
    
    
};



#endif /* Credits_hpp */
