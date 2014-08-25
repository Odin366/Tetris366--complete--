#pragma once

#include "Globals.h"
#include "CBlock.h"

class Board
{
public:
    Board(int xPos, int yPos);
    ~Board();

    void HandleEvents();

    void Update(); 
    void UpdateHUD();

    void Draw();
    void DrawHUD();

    void GenerateBlock();

    void ClearLines();
    void ShiftBlocksDown(int startRow);

    void SwapHeldBlock();


    void SetTextColor(int r, int g, int b);

    bool GameEnded();

    void SetBorderColor(SDL_Color clr)
    {
        mBorderClr = clr;
    }

    int GetXPos()
    {
        return mXPos;
    }

    int GetYPos()
    {
        return mYPos;
    }

    int GetScore()
    {
        return mScore;
    }

    void SetDelay(int delay)
    {
        mDelay = delay;
    }

    void IncrementSoftDropBonus()
    {
        mSoftDropBonus++;
    }

    int GetSoftDropBonus()
    {
        return mSoftDropBonus;
    }

    int GetLevel()
    {
        return mLevel;
    }

private:

    // Line clear sound
    Mix_Chunk *mLineClearSound;

    // Is the game over
    bool mGameOver;

    // Level number
    int mLevel;

    // Player score
    int mScore;

    // Number of lines cleared at the same time
    int mLinesScored;    

    // Total number of lines cleared
    int mLinesCleared;

    // Held block text
    Texture mHeldBlockText;

    // Next block text
    Texture mNextBlockText;

    // Score texture
    Texture mScoreText;

    // Lines cleared text
    Texture mLinesClearedText;

    // Level text
    Texture mLevelText;

    // Stores text color
    SDL_Color mTextColor;
    SDL_Color mTextColorMod;

    // Board texture
    Texture mGridTexture;

    // Tile textures
    Texture mBlockTextures[TILE_TYPES];

    // Landed matrix
    int mLandedGrid[GRID_HEIGHT][GRID_WIDTH]; 

    // Border rect
    SDL_Rect mBorder;

    // Clip rect
    SDL_Rect mClipRect;

    // Border Color
    SDL_Color mBorderClr;

    // Board position
    int mXPos;
    int mYPos;

    // Current block
    Block *mCurrentBlock;

    // Next block preview
    Block *mNextBlock;

    // Held block
    Block *mHeldBlock;

    // Was a block swapped recently
    bool mSwappedRecently;

    // Base time delay amount
    int mModDelay;

    // Modifiable Time delay amount
    int mDelay;

    // Timer for delay
    int mDelayCount;

    // Bonus points for soft dropping
    int mSoftDropBonus;

    // Play sounds
    bool mPlaySounds;

    // Show ghost
    bool mShowGhost;
};