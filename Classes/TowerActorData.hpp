//
//  TowerActorData.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/23.
//
//

#ifndef TowerActorData_hpp
#define TowerActorData_hpp

#include <stdio.h>


class TowerActorData {
public:
    std::string shooterName = "";
    std::string shootThing = "";
    
    int attackFrameNumber = 0;
    int attackEffectFrameNumber = 0;
    int dispatchSoldierFrameNumber = 0;
    
    int attackBaseFrameNumber = 0;
    int attackTopFrameNumber = 0;
    int attackSmokeFrameNumber = 0;
    int attackReloadFrameNumber = 0;
    int attackArtilleryLeftFrameNumber = 0;
    int attackArtilleryRightFrameNumber = 0;
};

#endif /* TowerActorData_hpp */
