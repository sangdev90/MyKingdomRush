//
//  ArcherTower.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/27.
//
//

#ifndef ArcherTower_hpp
#define ArcherTower_hpp

#include <stdio.h>
#include "Tower.hpp"

class ArcherTower : public Tower{
public:
    
    static ArcherTower *createArcherTower();
    
    ArcherTower():
    Tower("archer_tower") {};
    ~ArcherTower() = default;
    
    virtual void updateLevel();
    virtual bool initTower();
    
private:
    
};

#endif /* ArcherTower_hpp */
