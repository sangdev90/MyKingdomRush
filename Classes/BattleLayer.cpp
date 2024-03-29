//
//  BattleLayer.cpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/8.
//
//

#include <vector>
#include "BattleLayer.hpp"
#include "BattleUILayer.hpp"
#include "Monster.hpp"
#include "GameData.hpp"
#include "Tower.hpp"

#include "ResourcesPath.h"
#include "ToolFunction.hpp"

#include "json/rapidjson.h"
#include "json/stringbuffer.h"
#include "json/document.h"

USING_NS_CC;

BattleLayer *BattleLayer::create(const std::string &stage){
    BattleLayer *pRet = new (std::nothrow) BattleLayer(stage);
    if (pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    delete pRet;
    pRet = nullptr;
    return nullptr;
}

bool BattleLayer::init(){
    if (!Layer::init()){
        return false;
    }
    
    _battleUILayer = BattleUILayer::create();
    this->addChild(_battleUILayer, 100);
    
    this->_loadBattle();
    this->_dealMapPositoinData();
    this->_dealMapScaleData();
    this->_loadBattleData();
    
    _drawSomthingOnMap();
    
    //MARK: test
    _someTestCode();
    
    return true;
}

void BattleLayer::onEnter(){
    Layer::onEnter();
    
    _touchListener = EventListenerTouchAllAtOnce::create();
    _touchListener->onTouchesBegan = [&](const std::vector<Touch *> &touches, Event *event){
        
//        if (touches.size() == 1){
//            Touch *touch = touches[0];
//            Vec2 roadPoint = _battleMap->convertToNodeSpace(touch->getLocation());
//            CCLOG("Road Point : (%f, %f)", roadPoint.x, roadPoint.y);
//        }
        
    };
    _touchListener->onTouchesMoved = [&](const std::vector<Touch *> &touches, Event *event){
        if (touches.size() == 1){
            Touch *touch = touches[0];
            Vec2 mapPosition = _battleMap->getPosition();
            Vec2 delta = touch->getDelta();
            if (mapPosition.x + delta.x > _mapMinPosition.x && mapPosition.x + delta.x < _mapMaxPosition.x){
                _battleMap->setPosition(mapPosition.x + delta.x, mapPosition.y);
            }else if (mapPosition.x + delta.x < _mapMinPosition.x){
                _battleMap->setPosition(_mapMinPosition.x, mapPosition.y);
            }else if (mapPosition.x + delta.x > _mapMaxPosition.x){
                _battleMap->setPosition(_mapMaxPosition.x, mapPosition.y);
            }
            
            mapPosition = _battleMap->getPosition();
            if (mapPosition.y + delta.y > _mapMinPosition.y && mapPosition.y + delta.y < _mapMaxPosition.y){
                _battleMap->setPosition(mapPosition.x, mapPosition.y + delta.y);
            }else if (mapPosition.y + delta.y < _mapMinPosition.y){
                _battleMap->setPosition(mapPosition.x, _mapMinPosition.y);
            }else if (mapPosition.y + delta.y > _mapMaxPosition.y){
                _battleMap->setPosition(mapPosition.x, _mapMaxPosition.y);
            }
        }
        
        if (touches.size() == 2){
            Touch *touch1 = touches[0];
            Touch *touch2 = touches[1];
            float previousDistance = distanceBetweenTwoVec2(touch1->getPreviousLocation(), touch2->getPreviousLocation());
            float distance = distanceBetweenTwoVec2(touch1->getLocation(), touch2->getLocation());
            if (fabsf(distance - previousDistance) < 5){
                return;
            }else {
                float scale = _battleMap->getScale() * (distance / previousDistance);
                if (scale > _mapMaxScale || scale < _mapMinScale){
                    return;
                }
                _battleMap->setScale(scale);
                this->_dealMapPositoinData();
                Vec2 currentbBattleMapPosition = _battleMap->getPosition();
                Size currentBattleMapSize = Size(_battleMap->getContentSize().width * _currentMapScale, _battleMap->getContentSize().height * _currentMapScale);
                if (currentbBattleMapPosition.x - currentBattleMapSize.width / 2 > 0){
                    _battleMap->setPosition(currentBattleMapSize.width / 2, currentbBattleMapPosition.y);
                }
                if (currentbBattleMapPosition.x + currentBattleMapSize.width / 2 < _visibleSize.width){
                    _battleMap->setPosition(_visibleSize.width - currentBattleMapSize.width / 2, currentbBattleMapPosition.y);
                }
                
                currentbBattleMapPosition = _battleMap->getPosition();
                if (currentbBattleMapPosition.y - currentBattleMapSize.height / 2 > 0){
                    _battleMap->setPosition(currentbBattleMapPosition.x, currentBattleMapSize.height / 2);
                }
                if (currentbBattleMapPosition.y + currentBattleMapSize.height / 2 < _visibleSize.height){
                    _battleMap->setPosition(currentbBattleMapPosition.x, _visibleSize.height - currentBattleMapSize.height / 2);
                }

            }
        }
        
    };
    _touchListener->onTouchesEnded = [](const std::vector<Touch *> &touches, Event *evnet){
        
    };
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_touchListener, this);
    
    
}

void BattleLayer::onExit(){
    Layer::onExit();
    if (_touchListener){
        Director::getInstance()->getEventDispatcher()->removeEventListener(_touchListener);
    }
}

Vec2 BattleLayer::getSomethingOnMapWorldPoint(cocos2d::Sprite *node){
    Vec2 worldPoint = _battleMap->convertToWorldSpace(node->getPosition());
    return worldPoint;
}

void BattleLayer::_loadBattle(){
    _visibleSize = Director::getInstance()->getVisibleSize();
    
    _battleMap = Sprite::create(BATTLE_MAP_STAGE_1);
    _mapSize = _battleMap->getContentSize();
    _battleMap->setScale(0.6);
    _currentMapScale = 0.6;
    _battleMap->setPosition(_visibleSize.width / 2, _visibleSize.height / 2);
    this->addChild(_battleMap, 1);
    
}

void BattleLayer::_dealMapPositoinData(){
    
    _currentMapScale = _battleMap->getScale();
    
    _mapMinPosition = Vec2(_visibleSize.width - _mapSize.width * _currentMapScale / 2, _visibleSize.height - _mapSize.height * _currentMapScale / 2);
    _mapMaxPosition = Vec2(_mapSize.width * _currentMapScale / 2, _mapSize.height * _currentMapScale / 2);
}

void BattleLayer::_dealMapScaleData(){
    _mapMaxScale = 1;
    
    float widthScale = _visibleSize.width / _mapSize.width;
    float heightScale = _visibleSize.height / _mapSize.height;
    
    _mapMinScale = widthScale > heightScale ? widthScale : heightScale;
    
    CCLOG("Min Scale %f", _mapMinScale);
}

void BattleLayer::_loadBattleData(){
    
    std::string jsonPath = std::string("res/data/battle/battle_data_") + _stage + ".json";
//    CCLOG("Battle Data JSON Path : %s", jsonPath.c_str());
    std::string fullJsonPath = FileUtils::getInstance()->fullPathForFilename(jsonPath);
//    CCLOG("Battle Data JSON Full Path : %s", fullJsonPath.c_str());
    std::string jsonStringData = FileUtils::getInstance()->getStringFromFile(fullJsonPath);
//    CCLOG("Battle Data JSON String : %s", jsonStringData.c_str());
    
    rapidjson::Document battleJsonDocument;
    battleJsonDocument.Parse<0>(jsonStringData.c_str());
    if (battleJsonDocument.HasParseError()){
        CCLOG("Parse JSON : %s \n Error : %u", jsonPath.c_str(), battleJsonDocument.GetParseError());
    }else {
        if (battleJsonDocument.IsObject()){
            
            _battleData.coin = battleJsonDocument["coin"].GetInt();
            _battleData.hp = battleJsonDocument["hp"].GetInt();
            
//            if (battleJsonDocument["defencePoint"].IsArray()){
//                for (int index = 0; index < battleJsonDocument["defencePoint"].Size(); ++index){
//                    Vec2 point = Vec2(battleJsonDocument["defencePoint"][index]["x"].GetInt(), battleJsonDocument["defencePoint"][index]["y"].GetInt());
//                }
//            }
            
            if (battleJsonDocument["towerBuildPoint"].IsArray()){
                CCLOG("TowerBuildPoint is Array");
                for (int index = 0; index < battleJsonDocument["towerBuildPoint"].Size(); ++index){
                    Vec2 point = Vec2(battleJsonDocument["towerBuildPoint"][index]["x"].GetInt(), battleJsonDocument["towerBuildPoint"][index]["y"].GetInt());
                    _battleData.towerBuildPoint.push_back(point);
                }
            }

            if (battleJsonDocument["npcTowerBuildPoint"].IsArray()){
                for (int index = 0; index < battleJsonDocument["npcTowerBuildPoint"].Size(); ++index){
                    Vec2 point = Vec2(battleJsonDocument["npcTowerBuildPoint"][index]["x"].GetInt(), battleJsonDocument["npcTowerBuildPoint"][index]["y"].GetInt());
                    _battleData.npcTowerBuildPoint.push_back(point);
                }
            }
            
            if (battleJsonDocument["monster"].IsArray()){
                for (int index = 0; index < battleJsonDocument["monster"].Size(); ++index){
                    std::string monster = battleJsonDocument["monster"][index].GetString();
                    _battleData.monster.push_back(monster);
                }
            }
            
        }
    }
    
    printBattleData(_battleData);
    
    
    //astar and path
    _battleAStarData = parseBattleAStarDataWithPlistFile(getBattleMapAstarDataPlistFilePathWithStageName(_stage));
    _battlePathData = parseBattlePathDataByPlistFile(getBattleMapPathDataPlistFilePathWithStageName(_stage));
    
//    for (std::vector<BattleAStarGridData>::iterator iter = _battleAStarData.begin(); iter != _battleAStarData.end(); ++iter){
//        CCLOG("(%d, %d) : %d", iter->row, iter->column, iter->walkable);
//    }
    
    GameData::getInstance()->loadTowerData();
    GameData::getInstance()->loadTowerActorData();
    GameData::getInstance()->loadTowerShooterData();
    GameData::getInstance()->loadTowerShootThingData();
    
}

void BattleLayer::_drawSomthingOnMap(){
    _testDrawNode = DrawNode::create();
    _battleMap->addChild(_testDrawNode, 0);
    
    float width = 34;
    float height = 30;
//    for (std::vector<BattleAStarGridData>::iterator iter = _battleAStarData.begin(); iter != _battleAStarData.end(); ++iter){
//        if (iter->walkable){
//            _testDrawNode->drawRect(Vec2(iter->column * width, iter->row * height), Vec2((iter->column + 1) * width, (iter->row + 1) * height), Color4F(100, 100, 100, 100));
//        } else {
//            _testDrawNode->drawRect(Vec2(iter->column * width, iter->row * height), Vec2((iter->column + 1) * width, (iter->row + 1) * height), Color4F(200, 200, 200, 100));
//        }
//    }
    
//    for (auto iter1 = _battlePathData.begin(); iter1 != _battlePathData.end(); ++iter1){
//        for (auto iter2 = iter1->begin(); iter2 != iter1->end(); ++iter2){
//            for (auto iter3 = iter2->begin(); iter3 != iter2->end(); ++iter3){
////                CCLOG("(%f, %f)", iter3->x, iter3->y);
//                _testDrawNode->drawPoint(*iter3, 4, Color4F(100, 100, 100, 255));
//            }
//        }
//    }
    
}

void BattleLayer::_someTestCode(){
    
    
//    for (int i =0; i< 2; ++i){
//        for (int j = 0; j < 3; ++j){
//            SpriteFrameCache::getInstance()->addSpriteFramesWithFile(getMonsterSpriteSheetPlistPath(GameData::getInstance()->monsterName.desertThug));
//            GameData::getInstance()->loadMonsterData();
//            Monster *testMonster = Monster::createWithName(GameData::getInstance()->monsterName.desertThug, _battlePathData[i][j]);
//            _battleMap->addChild(testMonster, 1);
//        }
//    }

    //Add Tower
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("res/image/tower/tower.plist");
    for (auto towerBuildPoint : _battleData.towerBuildPoint){
        Tower *testTower = Tower::createTowerByName(GameData::getInstance()->towerName.archerTower, this);
        testTower->setAnchorPoint(Vec2(0.5, 0));
        testTower->setPosition(towerBuildPoint);
        _battleMap->addChild(testTower);
        towerArray.push_back(testTower);
    }
    
    //Add Monster
    GameData::getInstance()->loadMonsterData();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(getMonsterSpriteSheetPlistPath(GameData::getInstance()->monsterName.desertThug));
//    int bigPathNumber = static_cast<int>(_battlePathData.size());
//    int smallPathNumber = static_cast<int>(_battlePathData[0].size());
//    Monster *testMonster = Monster::createWithName(GameData::getInstance()->monsterName.desertThug, _battlePathData[bigPathNumber * CCRANDOM_0_1()][smallPathNumber * CCRANDOM_0_1()]);
//    _battleMap->addChild(testMonster, 1);
//    monsterArray.push_back(testMonster);
    this->schedule([&](float dt){
        
        int bigPathNumber = static_cast<int>(_battlePathData.size());
        int smallPathNumber = static_cast<int>(_battlePathData[0].size());
        Monster *testMonster = Monster::createWithName(GameData::getInstance()->monsterName.desertThug, _battlePathData[bigPathNumber * CCRANDOM_0_1()][smallPathNumber * CCRANDOM_0_1()]);
        _battleMap->addChild(testMonster, 1);
        monsterArray.push_back(testMonster);
        
    }, 2, "TestCodeAddMonster");
    
//    this->schedule([&](float dt){
//        
//        for (auto tower : _towerArray){
//            tower->attack(tower->convertToNodeSpace(tower->convertToWorldSpace(tower->getPosition())),
//                          tower->convertToNodeSpace(tower->convertToWorldSpace(Vec2(tower->getPositionX() + 50, tower->getPositionY() + 50))),
//                          [&](){
//                              CCLOG("%s", _battleMap->getDescription().c_str());
//                          });
//        }
//        
//    }, 3.0, "Test Tower Attack");
    
}


















