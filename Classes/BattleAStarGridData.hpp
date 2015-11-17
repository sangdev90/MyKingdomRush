//
//  BattleAStarGridData.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/17.
//
//

#ifndef BattleAStarGridData_hpp
#define BattleAStarGridData_hpp

#include <stdio.h>

class BattleAStarGridData {
public:
    
    BattleAStarGridData(int r, int c, int w):
    row(r), column(c), walkable(w) {};
    
    int row;
    int column;
    int walkable;
};

#endif /* BattleAStarGridData_hpp */
