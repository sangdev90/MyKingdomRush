//
//  WaitLoad.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/10/31.
//
//

#ifndef WaitLoad_hpp
#define WaitLoad_hpp

#include <stdio.h>
#include "cocos2d.h"

class WaitLoad : public cocos2d::Layer{
    
public:
    
    static WaitLoad *getInstance();
    static WaitLoad *selfPointer;
    
    void open();
    void close(const std::function<void()> &callback);
    
    virtual bool init();
    
private:
    
    static WaitLoad *create();
    
    bool isOpen = true;
    WaitLoad() = default;
    
    cocos2d::Sprite *leftBackground;
    cocos2d::Sprite *rightBackground;
    cocos2d::Sprite *leftLogo;
    cocos2d::Sprite *rightLogo;
    
};

#endif /* WaitLoad_hpp */
