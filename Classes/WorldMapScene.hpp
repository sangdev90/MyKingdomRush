//
//  WorldMapScene.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/4.
//
//

#ifndef WorldMapScene_hpp
#define WorldMapScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "WorldMapUILayer.hpp"
#include "WorldMapLayer.hpp"

class WorldMapScene : public cocos2d::Scene{
    
public:
    static WorldMapScene *create();
    
    virtual bool init();
    
private:
    WorldMapLayer *_worldMapLayer;
};

#endif /* WorldMapScene_hpp */
