#pragma once

#include "Globals.h"

class Block
{
public:
    Block(int type, int orientation, Texture *texture);
    ~Block();

    void HandleEvents(int landedGrid[GRID_HEIGHT][GRID_WIDTH]);

    void Draw(int gridX, int gridY, int landedGrid[GRID_HEIGHT][GRID_WIDTH]);
    void DrawGhost(int gridX, int gridY, int landedGrid[GRID_HEIGHT][GRID_WIDTH]);

    void UpdatePosition(int landedGrid[GRID_HEIGHT][GRID_WIDTH]);

    void CheckBounds(int gridX, int gridY, int landedGrid[GRID_HEIGHT][GRID_WIDTH]);
    bool CheckPotentialCollision(int landedGrid[GRID_HEIGHT][GRID_WIDTH]); // Checks if current shape is colliding

    Array_3D GetBlockMatrix()
    {
        return mBlockMatrix;
    }

    bool HasLanded()
    {
        return mLanded;
    }

    int GetGridX()
    {
        return mGridX;
    }

    int GetGridY()
    {
        return mGridY;
    }

    void SetGridX(int x)
    {
        mGridX = x;
    }

    void SetGridY(int y)
    {
        mGridY = y;
    }

    int GetWidth()
    {
        return mWidth;
    }

    int GetHeight()
    {
        return mHeight;
    }

    int GetType()
    {
        return mType;
    }

    int GetDirection()
    {
        return mOrientation;
    }

    void SetDirection(int direction)
    {
        mOrientation = direction;
    }

    void IncrementY()
    {
        mGridY++;
    }

    void ShowGhost(bool status)
    {
        mShowGhost = status;
    }

    void PlaySounds(bool status)
    {
        mPlayingSounds = status;
    }

private:    


    // Lets you mute block sounds
    bool mPlayingSounds;

    // Toggle ghost block
    bool mShowGhost;

    // Block type
    int mType;

    // Block orientation
    int mOrientation;

    // Has the block landed yet
    bool mLanded;

    // Block top left position
    int mGridX;
    int mGridY;

    // Block dimensions
    int mWidth;
    int mHeight;

    // Block matrices
    Array_3D mBlockMatrix;

    // Texture
    Texture *mTexture;

    // Movement Sound effect
    Mix_Chunk *mMoveSound;

    // Rotation Sound effect
    Mix_Chunk *mRotationSound;

    // Ghost block texture
    Texture mGhostTexture;

    // Ghost x position
    int mGhostGridX;
    
    // ghost y position
    int mGhostGridY;
};