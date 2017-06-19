#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "Board.h"
#include "Game.h"

class MainScene : public cocos2d::Layer
{
    float mTime;
    Board *mBoard;
    Game *mGame;
    
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;
    
    CREATE_FUNC(MainScene);
    
    void drawRectangle(int pX1, int pY1, int pX2, int pY2);
    void clearScreen();
    int getScreenHeight();
    
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;
    
    void update(float) override;
};

#endif // __HELLOWORLD_SCENE_H__
