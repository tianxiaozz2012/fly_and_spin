#include "GameScene.h"
#include "CircleAction.h"
#include "GameSceneTouchLayer.h"
#include "SceneManager.h"
USING_NS_CC;


static GameScene *_sharedGameScene = NULL;
GameScene* GameScene::shareGameScene()
{
    if(!_sharedGameScene){
        _sharedGameScene = new GameScene();
        if (_sharedGameScene && _sharedGameScene->initWithPhysics())
        {
//            _sharedGameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
            _sharedGameScene->getPhysicsWorld()->setGravity(cocos2d::Vect(0,0));
            
            _sharedGameScene->initLayer();
        }
        

    }

    return _sharedGameScene;
}

void GameScene::initLayer(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    

    gameLayer = GameSceneTouchLayer::create();
    gameLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    gameLayer->setPosition(Point(0, 0));
    _sharedGameScene->addChild(gameLayer, 10);
    
    menuLayer = GameMenuLayer::create();
    menuLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    menuLayer->setPosition(Point(0, 0));
    _sharedGameScene->addChild(menuLayer, 12);
    
    backgroundLayer = GameBackgroundLayer::create();
    backgroundLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
    backgroundLayer->setPosition(Point(0, 0));
    _sharedGameScene->addChild(backgroundLayer, 0);
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(GameScene::gameOver), "gameover", NULL);
}

void GameScene::reset(){
    NotificationCenter::getInstance()->removeObserver(this, "gameover");
    removeAllChildrenWithCleanup(true);
    _sharedGameScene = NULL;
}

void GameScene::gameOver(Ref* sender){
    UserDefault::getInstance()->setIntegerForKey("current_score", gameLayer->score);
    SceneManager::sharedSceneManager()->changeScene(SceneManager::en_GameoverScene);
}

void GameScene::pauseGame(){
    if(pauseLayer){
        pauseLayer->setVisible(true);
    }
    else{
        Size visibleSize = Director::getInstance()->getVisibleSize();
        pauseLayer = GamePauseLayer::create();
        pauseLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
        pauseLayer->setPosition(Point(0, 0));
        _sharedGameScene->addChild(pauseLayer, 15);
    }
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    Director::getInstance()->pause();
}
