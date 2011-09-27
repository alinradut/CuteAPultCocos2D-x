//
//  HelloWorldScene.h
//  CuteAPultCocos2D-x
//
//  Created by Clawoo on 9/8/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#ifndef __HELLO_m_worldH__
#define __HELLO_m_worldH__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

class HelloWorld : public cocos2d::CCLayer {
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    // adds a new sprite at a given coordinate
    virtual void draw();
    void tick(cocos2d::ccTime dt);
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void createBullets(int count);
    bool attachBullet();
    void resetBullet();
    void resetGame();
    
    void createTargets();
    void createTarget(const char *imageName, 
                      cocos2d::CCPoint position, 
                      float rotation, 
                      bool isCircle, 
                      bool isStatic, 
                      bool isEnemy);

private:
    std::vector<b2Body *> m_bullets;
    std::vector<b2Body *> m_targets;
    std::vector<b2Body *> m_enemies;

    int m_currentBullet;
    b2World* m_world;
    b2Body* m_groundBody;
    b2Fixture *m_armFixture;
    b2Body *m_armBody;
    b2RevoluteJoint *m_armJoint;
    b2MouseJoint *m_mouseJoint;
    
    b2Body *m_bulletBody;
    b2WeldJoint *m_bulletJoint;
    
    
    bool m_releasingArm;
};

#endif // __HELLO_m_worldH__
