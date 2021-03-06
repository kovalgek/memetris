/*****************************************************************************************
/* File: Game.h
/* Desc: General class for the game
/*
/* gametuto.com - Javier L�pez L�pez (javilop.com)
/*
/*****************************************************************************************
/*
/* Creative Commons - Attribution 3.0 Unported
/* You are free:
/*	to Share � to copy, distribute and transmit the work
/*	to Remix � to adapt the work
/*
/* Under the following conditions:
/* Attribution. You must attribute the work in the manner specified by the author or licensor 
/* (but not in any way that suggests that they endorse you or your use of the work).
/*
/*****************************************************************************************/

#ifndef _GAME_
#define _GAME_

// ------ Includes -----

#include "Board.h"
#include "Pieces.h"

#include <time.h>

class MainScene;

// ------ Defines -----

#define WAIT_TIME 700			// Number of milliseconds that the piece remains before going 1 block down */ 


// --------------------------------------------------------------------------------
//									 Game
// --------------------------------------------------------------------------------

class Game
{
public:

	Game			(Board *pBoard, Pieces *pPieces, MainScene *pIO, int pScreenHeight);

	void drawScene ();
	void createNewPiece ();

	int mPosX, mPosY;				// Position of the piece that is falling down
	int mPiece, mRotation;			// Kind and rotation the piece that is falling down

private:

	int mScreenHeight;				// Screen height in pixels
	int mNextPosX, mNextPosY;		// Position of the next piece
	int mNextPiece, mNextRotation;	// Kind and rotation of the next piece

	Board *mBoard;
	Pieces *mPieces;
	MainScene *mIO;

	int getRand (int pA, int pB);
	void initGame();
	void drawPiece (int pX, int pY, int pPiece, int pRotation);
	void drawBoard ();
};

#endif // _GAME_
