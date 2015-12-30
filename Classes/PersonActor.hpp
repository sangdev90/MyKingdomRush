//
//  PersonActor.hpp
//  KingdomRush
//
//  Created by 贾佳菊 on 15/11/29.
//
//

#ifndef PersonActor_hpp
#define PersonActor_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ToolFunction.hpp"

class PersonActorAnimatoinData {
public:
    int numberOfAttackAnimationFrame = 0;
    int numberOfDieAnimationFrame = 0;
    int numberOfForwardAnimationFrame = 0;
    int numberOfBackwardAnimationFrame = 0;
    int numberOfTowardAniamtionFrame = 0;
    int numberOfRemoteAttackAnimationFrame = 0;
    int numberOfReleaseSkillAnimationFrame = 0;
};

class PersonActor : public cocos2d::Sprite{
public:
    static PersonActor *createPersonActorByName(const std::string &side, const std::string &name, const PersonActorAnimatoinData &animationData);
    
    PersonActor(const std::string &name):
    _name(name) {};
    virtual ~PersonActor() = 0;
    
    virtual void playAttackAnimation(const std::function<void ()> &callback);
    virtual void playDieAnimation(const std::function<void ()> &callback);
    virtual void playTowardAnimation(const std::function<void ()> &callback);
    virtual void playForwardAnimation(const std::function<void ()> &callback);
    virtual void playBackwardAnimation(const std::function<void ()> &callback);
    
    virtual bool initWithAnimationData(const PersonActorAnimatoinData &animationData);
    
    void turnAround(const std::string &faceTo){
        if (faceTo != _faceTo){
            _faceTo = faceTo;
            if (faceTo == "left"){
                this->setFlippedX(true);
            }else if (faceTo == "right"){
                this->setFlippedX(false);
            }
        }
    };
    
    void prepareAnimation(cocos2d::Vector<cocos2d::SpriteFrame *> &frameArray, const std::string &animation, int numberOfFrame){
//        CCLOG("%s, %s, %d", __func__, animation.c_str(), numberOfFrame);
        
        for (int frameIndex = 0; frameIndex < numberOfFrame; ++frameIndex){
            std::string frameName = getMonsterAnimationFrameName(_name, animation, frameIndex);
//            CCLOG("Monster 动画名字：%s", frameName.c_str());
            frameArray.pushBack(getMonsterSpriteFrameByName(frameName));
        }
    }
    
protected:
    
    std::string _side = ""; // "soldier" or "monster"
    std::string _name = "";
    std::string _faceTo = "right";
    std::string _state = "normal"; // "attack" or "die" or "forward" or "backward" or "toward" and son on
    float _defaultDelayPerUnit;
    
    int _numberOfAttackAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _attackAniamtionFrameArray;
    
    int _numberOfDieAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame*> _dieAnimationFrameArray;
    
    int _numberOfForwardAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _runForwardAnimationFrameArray;
    
    int _numberOfBackwardAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _runBackwardAnimationFrameArray;
    
    int _numberOfTowardAnimationFrame;
    cocos2d::Vector<cocos2d::SpriteFrame *> _runTowardAnimationFrameArray;
    
    void _playAnimation(const cocos2d::Vector<cocos2d::SpriteFrame *> &frameArray, const std::function<void ()> &callback){
        cocos2d::Animation *animation = cocos2d::Animation::createWithSpriteFrames(frameArray);
        animation->setDelayPerUnit(_defaultDelayPerUnit);
        cocos2d::Animate *animate = cocos2d::Animate::create(animation);
        cocos2d::Sequence *action = cocos2d::Sequence::create(animate,
                                                              cocos2d::CallFuncN::create([&, callback](cocos2d::Node *target){
                                                                _state = "normal";
                                                                callback();
                                                              }),
                                                              NULL);
        this->runAction(action);
    };
    
    std::string _getPerosonActorNormalSpriteName(){
        std::string personActorNormalSpriteName = getMonsterAnimationFrameName(_name, "toward", 0);
        return personActorNormalSpriteName;
    }
};

#endif /* PersonActor_hpp */
