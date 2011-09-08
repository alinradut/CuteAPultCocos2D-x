//
//  HelloWorldScene.cpp
//  CuteAPultCocos2D-x
//
//  Created by Clawoo on 9/8/11.
//  Copyright __MyCompanyName__ 2011. All rights reserved.
//
#include "HelloWorldScene.h"

using namespace cocos2d;

#define PTM_RATIO       32
#define FLOOR_HEIGHT    62.0f
enum 
{
	kTagTileMap = 1,
	kTagSpriteManager = 1,
	kTagAnimation1 = 1,
}; 

HelloWorld::HelloWorld()
{
	setIsTouchEnabled( true );
    
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	//UXLOG(L"Screen width %0.2f screen height %0.2f",screenSize.width,screenSize.height);
    
	// Define the gravity vector.
	b2Vec2 gravity;
	gravity.Set(0.0f, -10.0f);
	
	// Do we want to let bodies sleep?
	bool doSleep = true;
    
	// Construct a world object, which will hold and simulate the rigid bodies.
	world = new b2World(gravity, doSleep);
    
	world->SetContinuousPhysics(true);
    
    /*	
     m_debugDraw = new GLESDebugDraw( PTM_RATIO );
     world->SetDebugDraw(m_debugDraw);
     
     uint flags = 0;
     flags += b2DebugDraw::e_shapeBit;
     flags += b2DebugDraw::e_jointBit;
     flags += b2DebugDraw::e_aabbBit;
     flags += b2DebugDraw::e_pairBit;
     flags += b2DebugDraw::e_centerOfMassBit;
     m_debugDraw->SetFlags(flags);		
     */
	
    CCSprite *sprite = CCSprite::spriteWithFile("bg.png");
    sprite->setAnchorPoint(CCPointZero);
    this->addChild(sprite, -1);
    
    sprite = CCSprite::spriteWithFile("catapult_base_2.png");
    sprite->setAnchorPoint(CCPointZero);
    sprite->setPosition(CCPointMake(181.0, FLOOR_HEIGHT));
    this->addChild(sprite, 0);
    
    sprite = CCSprite::spriteWithFile("squirrel_1.png");
    sprite->setAnchorPoint(CCPointZero);
    sprite->setPosition(CCPointMake(11.0, FLOOR_HEIGHT));
    this->addChild(sprite, 0);
    
    sprite = CCSprite::spriteWithFile("catapult_base_1.png");
    sprite->setAnchorPoint(CCPointZero);
    sprite->setPosition(CCPointMake(181.0, FLOOR_HEIGHT));
    this->addChild(sprite, 9);
    
    sprite = CCSprite::spriteWithFile("squirrel_2.png");
    sprite->setAnchorPoint(CCPointZero);
    sprite->setPosition(CCPointMake(240.0, FLOOR_HEIGHT));
    this->addChild(sprite, 9);
    
    sprite = CCSprite::spriteWithFile("fg.png");
    sprite->setAnchorPoint(CCPointZero);
    this->addChild(sprite, 10);
    
	// Define the ground body.
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0); // bottom-left corner
	
	// Call the body factory which allocates memory for the ground body
	// from a pool and creates the ground box shape (also from a pool).
	// The body is also added to the world.
	b2Body* groundBody = world->CreateBody(&groundBodyDef);
	
	// Define the ground box shape.
	b2PolygonShape groundBox;		
	
	// bottom
	groundBox.SetAsEdge(b2Vec2(0,0), b2Vec2(screenSize.width/PTM_RATIO,0));
	groundBody->CreateFixture(&groundBox, 0);
	
	// top
	groundBox.SetAsEdge(b2Vec2(0,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width/PTM_RATIO,screenSize.height/PTM_RATIO));
	groundBody->CreateFixture(&groundBox, 0);
	
	// left
	groundBox.SetAsEdge(b2Vec2(0,screenSize.height/PTM_RATIO), b2Vec2(0,0));
	groundBody->CreateFixture(&groundBox, 0);
	
	// right
	groundBox.SetAsEdge(b2Vec2(screenSize.width/PTM_RATIO,screenSize.height/PTM_RATIO), b2Vec2(screenSize.width/PTM_RATIO,0));
	groundBody->CreateFixture(&groundBox, 0);
    
	schedule( schedule_selector(HelloWorld::tick) );
}

HelloWorld::~HelloWorld()
{
	delete world;
	world = NULL;
	
	//delete m_debugDraw;
}

void HelloWorld::draw()
{
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states:  GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	
	//world->DrawDebugData();
	
	// restore default GL states
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);	
}

void HelloWorld::tick(ccTime dt)
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/
	
	int velocityIterations = 8;
	int positionIterations = 1;
    
	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	world->Step(dt, velocityIterations, positionIterations);
	
	//Iterate over the bodies in the physics world
	for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
	{
		if (b->GetUserData() != NULL) {
			//Synchronize the AtlasSprites position and rotation with the corresponding body
			CCSprite* myActor = (CCSprite*)b->GetUserData();
			myActor->setPosition( CCPointMake( b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO) );
			myActor->setRotation( -1 * CC_RADIANS_TO_DEGREES(b->GetAngle()) );
		}	
	}
}

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::node();
    
    // add layer as a child to scene
    CCLayer* layer = new HelloWorld();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}
