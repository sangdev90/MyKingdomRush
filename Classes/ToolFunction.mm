//
//  ToolFunction.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/10/31.
//
//

#import <Foundation/Foundation.h>
#include "ToolFunction.hpp"

std::vector<BattleAStarGridData> parseBattleAStarDataWithPlistFile(const std::string &plistPath){
    
    std::vector<BattleAStarGridData> battleAStarData;
    
    NSString *plistProjectPath = [NSString stringWithFormat:@"%s", plistPath.c_str()];
    NSString *plistPathNSSting = [[NSBundle mainBundle] pathForResource:plistProjectPath ofType:@"plist"];
    NSDictionary *astarDictionary = [[NSDictionary alloc] initWithContentsOfFile:plistPathNSSting];
    NSArray *gridArray = (NSArray *)[astarDictionary objectForKey:@"grid"];
    
    for (id arrayItem in gridArray){
        NSDictionary *grid = (NSDictionary *)arrayItem;
        
        int row = [((NSNumber *)[grid objectForKey:@"row"]) intValue];
        int column = [((NSNumber *)[grid objectForKey:@"column"]) intValue];
        int walkable = [((NSNumber *)[grid objectForKey:@"walkable"]) intValue];
        
        battleAStarData.push_back(BattleAStarGridData(row, column, walkable));
        
    }
    
    return battleAStarData;
    
}

std::vector<std::vector<std::vector<cocos2d::Vec2>>> parseBattlePathDataByPlistFile(const std::string &plistPath){
    
    NSString *plistProjectPath = [NSString stringWithFormat:@"%s", plistPath.c_str()];
    NSString *plistPathNSString = [[NSBundle mainBundle] pathForResource:plistProjectPath ofType:@"plist"];
    NSDictionary *pathDictionary = [[NSDictionary alloc] initWithContentsOfFile:plistPathNSString];
    NSArray *road = (NSArray *)[pathDictionary objectForKey:@"paths"];
    
    std::vector<std::vector<std::vector<cocos2d::Vec2>>> paths;
    
    for (id itemInRoad in road){
        NSArray *pathsOC = (NSArray *)itemInRoad;
        
        std::vector<std::vector<cocos2d::Vec2>> path;
        
        for (id itemPath in pathsOC){
            
            std::vector<cocos2d::Vec2> everyMonsterPath;
            for (id everyPath in itemPath){
                
                NSDictionary *pointDictionary = (NSDictionary *)everyPath;
                float positionX = [((NSNumber *)[pointDictionary objectForKey:@"x"]) floatValue];
                float positionY = [((NSNumber *)[pointDictionary objectForKey:@"y"]) floatValue];
                cocos2d::Vec2 pathPoint = cocos2d::Vec2(positionX * 2, positionY * 2);
                everyMonsterPath.push_back(pathPoint);
            }
            
            path.push_back(everyMonsterPath);
        }
        
        paths.push_back(path);
    }
    
    return paths;
    
}