#include "MainScene.h"

#include "Pieces.h"
#include "Board.h"
#include "Game.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool MainScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    // ----- Vars -----

    int mScreenHeight = getScreenHeight();
    
    // Pieces
    Pieces mPieces;
    
    // Board
    mBoard = new Board(&mPieces, mScreenHeight);
    
    // Game
    mGame = new Game(mBoard, &mPieces, this, mScreenHeight);
    mGame->drawScene ();			// Draw staff
    
    // creating a keyboard event listener
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(MainScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    this->scheduleUpdate();
    
    return true;
}

void MainScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    switch (keyCode)
    {
        case (EventKeyboard::KeyCode::KEY_RIGHT_ARROW):
        {
            if (mBoard->isPossibleMovement (mGame->mPosX + 1, mGame->mPosY, mGame->mPiece, mGame->mRotation))
                mGame->mPosX++;
            break;
        }

        case (EventKeyboard::KeyCode::KEY_LEFT_ARROW):
        {
            if (mBoard->isPossibleMovement (mGame->mPosX - 1, mGame->mPosY, mGame->mPiece, mGame->mRotation))
                mGame->mPosX--;
            break;
        }

        case (EventKeyboard::KeyCode::KEY_DOWN_ARROW):
        {
            if (mBoard->isPossibleMovement (mGame->mPosX, mGame->mPosY - 1, mGame->mPiece, mGame->mRotation))
                mGame->mPosY--;
            break;
        }

        case (EventKeyboard::KeyCode::KEY_X):
        {
            while (mBoard->isPossibleMovement(mGame->mPosX, mGame->mPosY, mGame->mPiece, mGame->mRotation)) { mGame->mPosY--; }

            mBoard->storePiece (mGame->mPosX, mGame->mPosY + 1, mGame->mPiece, mGame->mRotation);

            mBoard->deletePossibleLines ();

            if (mBoard->isGameOver())
            {
                exit(0);
            }

            mGame->createNewPiece();

            break;
        }

        case (EventKeyboard::KeyCode::KEY_Z):
        {
            if (mBoard->isPossibleMovement (mGame->mPosX, mGame->mPosY, mGame->mPiece, (mGame->mRotation + 1) % 4))
                mGame->mRotation = (mGame->mRotation + 1) % 4;
            
            break;
        }
            
        case (EventKeyboard::KeyCode::KEY_ESCAPE):
        {
            exit(0);
        }
            
        default: ;
    }
}

void MainScene::update(float delta) {
    
    mTime += delta;
    
    if (mTime > 0.2f)
    {
        mTime = 0;
        
        if (mBoard->isPossibleMovement (mGame->mPosX, mGame->mPosY - 1, mGame->mPiece, mGame->mRotation))
        {
            --mGame->mPosY;
        }
        else
        {
            mBoard->storePiece (mGame->mPosX, mGame->mPosY, mGame->mPiece, mGame->mRotation);
            mBoard->deletePossibleLines ();
            if (mBoard->isGameOver())
            {
                Director::getInstance()->end();
            }
            mGame->createNewPiece();
        }
    }
    clearScreen();
    mGame->drawScene();
}

void MainScene::drawRectangle(int pX1, int pY1, int pX2, int pY2) {
    
    auto rectWithBorder = DrawNode::create();
    Vec2 vertices[] =
    {
        Vec2(pX1,pY1),
        Vec2(pX1,pY2),
        Vec2(pX2,pY2),
        Vec2(pX2,pY1)
    };
    
    rectWithBorder->drawPolygon(vertices, 4, Color4F(1.0f,0.3f,0.3f,1), 0, Color4F(0.2f,0.2f,0.2f,1));
    this->addChild(rectWithBorder);
}

void MainScene::clearScreen() {
    this->removeAllChildren();
}

int MainScene::getScreenHeight() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return visibleSize.height;
}
