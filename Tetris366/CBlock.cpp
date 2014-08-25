#include "CBlock.h"
#include "CBoard.h"
#include "CoreGame.h"

Block::Block(int type, int orientation, Texture *texture)
{
    // Load the sounds
    mMoveSound    = Mix_LoadWAV("Sounds/plopnoise2.wav");
    mRotationSound = Mix_LoadWAV("Sounds/plopnoise1.wav");

    mPlayingSounds = true;
    mShowGhost = true;

    // Set texture
    mTexture = texture;

    // Load ghost texture
    mGhostTexture.LoadImage("Images/tile_ghost.png");

    // Set type
    mType = type;

    // Set landed
    mLanded = false;

    // Set position
    mGridX = 0;
    mGridY = 0;

    mGhostGridX = 0;
    mGhostGridY = 0;

    // Initialize shape

        // Set shape
        switch (type)
        {
            case BLOCK_TYPE_I:
            {
                // Set width
                mWidth       = BLOCK_BOUND_4;
                mHeight      = BLOCK_BOUND_4;
                mOrientation = orientation;

                // Resize block matrix

                    // Resize direction, row, then column vectors

                        // Resize direction vector (depth)
                        mBlockMatrix.resize(NUM_DIRECTIONS);

                            // Cycle through each orientation and set how many rows it will contain
                            for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                            {
                                // Resize rows vector (up and down)
                                mBlockMatrix[direction].resize(mHeight);

                                // Cycle through amount of rows and set how many columns they can contain
                                for(int row = 0; row < mHeight; row++)
                                {
                                    // Resize columns vector (left and right)
                                    mBlockMatrix[direction][row].resize(mWidth);
                                }
                            }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_4][BLOCK_BOUND_4]
                {
                    // Up
                    {
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 },
                        { 0, 0, 1, 0 },
                    },

                    // Right
                    {
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                        { 1, 1, 1, 1 },
                        { 0, 0, 0, 0 },
                    },

                    // Down
                    {
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                        { 0, 1, 0, 0 },
                    },

                    // Left
                    {
                        { 0, 0, 0, 0 },
                        { 1, 1, 1, 1 },
                        { 0, 0, 0, 0 },
                        { 0, 0, 0, 0 },
                    },
                };


                // Set shape
                for( int direction = 0; direction < NUM_DIRECTIONS; direction++ )
                {
                    for( int row = 0; row < mHeight; row++ )
                    {
                        for( int column = 0; column < mWidth; column++ )
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }

                break;
            }

            case BLOCK_TYPE_O:
            {

                // Set width
                mWidth       = BLOCK_BOUND_2;
                mHeight      = BLOCK_BOUND_2;
                mOrientation = orientation;

                // Resize block matrix

                    // Resize direction, row, then column vectors

                        // Resize direction vector (depth)
                        mBlockMatrix.resize(NUM_DIRECTIONS);

                            // Cycle through each orientation and set how many rows it will contain
                            for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                            {
                                // Resize rows vector (up and down)
                                mBlockMatrix[direction].resize(mHeight);

                                // Cycle through amount of rows and set how many columns they can contain
                                for(int row = 0; row < mHeight; row++)
                                {
                                    // Resize columns vector (left and right)
                                    mBlockMatrix[direction][row].resize(mWidth);
                                }
                            }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_2][BLOCK_BOUND_2]
                {
                    // Up
                    {
                        { 2, 2 },
                        { 2, 2 },
                    },

                    // Right
                    {
                        { 2, 2 },
                        { 2, 2 },
                    },


                    // Down
                    {
                        { 2, 2 },
                        { 2, 2 },
                    },

                    // Left
                    {
                        { 2, 2 },
                        { 2, 2 },
                    },
                };


                // Set shape
                for( int direction = 0; direction < NUM_DIRECTIONS; direction++ )
                {
                    for( int row = 0; row < mHeight; row++ )
                    {
                        for( int column = 0; column < mWidth; column++ )
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }

                break;
            }

            case BLOCK_TYPE_T:
            {
                // Set width
                mWidth       = BLOCK_BOUND_3;
                mHeight      = BLOCK_BOUND_3;
                mOrientation = orientation;

                // Resize block matrix

                // Resize direction, row, then column vectors

                // Resize direction vector (depth)
                mBlockMatrix.resize(NUM_DIRECTIONS);

                // Cycle through each orientation and set how many rows it will contain
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    // Resize rows vector (up and down)
                    mBlockMatrix[direction].resize(mHeight);

                    // Cycle through amount of rows and set how many columns they can contain
                    for(int row = 0; row < mHeight; row++)
                    {
                        // Resize columns vector (left and right)
                        mBlockMatrix[direction][row].resize(mWidth);
                    }
                }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_3][BLOCK_BOUND_3]
                {
                    // Up
                    {
                        { 0, 3, 0 },
                        { 3, 3, 3 },
                        { 0, 0, 0 },
                    },

                    // Right
                    {
                        { 0, 3, 0 },
                        { 0, 3, 3 },
                        { 0, 3, 0 },
                    },

                    // Down
                    {
                        { 0, 0, 0 },
                        { 3, 3, 3 },
                        { 0, 3, 0 },
                    },

                    // Left
                    {
                        { 0, 3, 0 },
                        { 3, 3, 0 },
                        { 0, 3, 0 },
                    },
                };


                // Set shape
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    for(int row = 0; row < mHeight; row++)
                    {
                        for(int column = 0; column < mWidth; column++)
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }

                break;
            }

            case BLOCK_TYPE_S:
            {
                // Set width
                mWidth  = BLOCK_BOUND_3;
                mHeight = BLOCK_BOUND_3;
                mOrientation = orientation;

                // Resize block matrix

                // Resize direction, row, then column vectors

                // Resize direction vector (depth)
                mBlockMatrix.resize(NUM_DIRECTIONS);

                // Cycle through each orientation and set how many rows it will contain
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    // Resize rows vector (up and down)
                    mBlockMatrix[direction].resize(mHeight);

                    // Cycle through amount of rows and set how many columns they can contain
                    for(int row = 0; row < mHeight; row++)
                    {
                        // Resize columns vector (left and right)
                        mBlockMatrix[direction][row].resize(mWidth);
                    }
                }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_3][BLOCK_BOUND_3]
                {
                    // Up
                    {
                        { 0, 4, 0 },
                        { 0, 4, 4 },
                        { 0, 0, 4 },
                    },

                    // Right
                    {
                        { 0, 0, 0 },
                        { 0, 4, 4 },
                        { 4, 4, 0 },
                    },

                    // Down
                    {
                        { 4, 0, 0 },
                        { 4, 4, 0 },
                        { 0, 4, 0 },
                    },

                    // Left
                    {
                        { 0, 4, 4 },
                        { 4, 4, 0 },
                        { 0, 0, 0 },
                    },
                };


                // Set shape
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    for(int row = 0; row < mHeight; row++)
                    {
                        for(int column = 0; column < mWidth; column++)
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }

                break;
            }

            case BLOCK_TYPE_Z:
            {
                // Set width
                mWidth       = BLOCK_BOUND_3;
                mHeight      = BLOCK_BOUND_3;
                mOrientation = orientation;

                // Resize block matrix

                // Resize direction, row, then column vectors

                // Resize direction vector (depth)
                mBlockMatrix.resize(NUM_DIRECTIONS);

                // Cycle through each orientation and set how many rows it will contain
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    // Resize rows vector (up and down)
                    mBlockMatrix[direction].resize(mHeight);

                    // Cycle through amount of rows and set how many columns they can contain
                    for(int row = 0; row < mHeight; row++)
                    {
                        // Resize columns vector (left and right)
                        mBlockMatrix[direction][row].resize(mWidth);
                    }
                }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_3][BLOCK_BOUND_3]
                {
                    // Up
                    {
                        { 0, 5, 0 },
                        { 5, 5, 0 },
                        { 5, 0, 0 },
                    },

                    // Right
                    {
                        { 5, 5, 0 },
                        { 0, 5, 5 },
                        { 0, 0, 0 },
                    },

                    // Down
                    {
                        { 0, 0, 5 },
                        { 0, 5, 5 },
                        { 0, 5, 0 },
                    },

                    // Left
                    {
                        { 0, 0, 0 },
                        { 5, 5, 0 },
                        { 0, 5, 5 },
                    },
                };


                // Set shape
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    for(int row = 0; row < mHeight; row++)
                    {
                        for(int column = 0; column < mWidth; column++)
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }

                break;
            }

            case BLOCK_TYPE_J:
            {
                // Set width
                mWidth       = BLOCK_BOUND_3;
                mHeight      = BLOCK_BOUND_3;
                mOrientation = orientation;

                // Resize block matrix

                // Resize direction, row, then column vectors

                // Resize direction vector (depth)
                mBlockMatrix.resize(NUM_DIRECTIONS);

                // Cycle through each orientation and set how many rows it will contain
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    // Resize rows vector (up and down)
                    mBlockMatrix[direction].resize(mHeight);

                    // Cycle through amount of rows and set how many columns they can contain
                    for(int row = 0; row < mHeight; row++)
                    {
                        // Resize columns vector (left and right)
                        mBlockMatrix[direction][row].resize(mWidth);
                    }
                }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_3][BLOCK_BOUND_3]
                {
                    // Up
                    {
                        { 0, 6, 0 },
                        { 0, 6, 0 },
                        { 6, 6, 0 },
                    },

                    // Right
                    {
                        { 6, 0, 0 },
                        { 6, 6, 6 },
                        { 0, 0, 0 },
                    },

                    // Down
                    {
                        { 0, 6, 6 },
                        { 0, 6, 0 },
                        { 0, 6, 0 },
                    },

                    // Left
                    {
                        { 0, 0, 0 },
                        { 6, 6, 6 },
                        { 0, 0, 6 },
                    },
                };


                // Set shape
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    for(int row = 0; row < mHeight; row++)
                    {
                        for(int column = 0; column < mWidth; column++)
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }


                break;
            }

            case BLOCK_TYPE_L:
            {
                // Set width
                mWidth = BLOCK_BOUND_3;
                mHeight = BLOCK_BOUND_3;
                mOrientation = orientation;

                // Resize block matrix

                // Resize direction, row, then column vectors

                // Resize direction vector (depth)
                mBlockMatrix.resize(NUM_DIRECTIONS);

                // Cycle through each orientation and set how many rows it will contain
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    // Resize rows vector (up and down)
                    mBlockMatrix[direction].resize(mHeight);

                    // Cycle through amount of rows and set how many columns they can contain
                    for(int row = 0; row < mHeight; row++)
                    {
                        // Resize columns vector (left and right)
                        mBlockMatrix[direction][row].resize(mWidth);
                    }
                }


                // Generate shape and orientations
                int shape[NUM_DIRECTIONS][BLOCK_BOUND_3][BLOCK_BOUND_3]
                {
                    // Up
                    {
                        { 0, 7, 0 },
                        { 0, 7, 0 },
                        { 0, 7, 7 },
                    },

                    // Right
                    {
                        { 0, 0, 0 },
                        { 7, 7, 7 },
                        { 7, 0, 0 },
                    },

                    // Down
                    {
                        { 7, 7, 0 },
                        { 0, 7, 0 },
                        { 0, 7, 0 },
                    },

                    // Left
                    {
                        { 0, 0, 7 },
                        { 7, 7, 7 },
                        { 0, 0, 0 },
                    },
                };


                // Set shape
                for(int direction = 0; direction < NUM_DIRECTIONS; direction++)
                {
                    for(int row = 0; row < mHeight; row++)
                    {
                        for(int column = 0; column < mWidth; column++)
                        {
                            mBlockMatrix[direction][row][column] = shape[direction][row][column];
                        }
                    }
                }

                break;
            }

        }

}

Block::~Block()
{
    // Free ghost block texture
    mGhostTexture.Free();

    // Set texture pointer to null
    mTexture = NULL;

    // Free the movement sound
    Mix_FreeChunk(mMoveSound);

    // Set the pointer to null
    mMoveSound = NULL;

    // Free the rotation sound
    Mix_FreeChunk(mRotationSound);

    // Set the pointer to null
    mRotationSound = NULL;
}

void Block::HandleEvents(int landedGrid[GRID_HEIGHT][GRID_WIDTH])
{
    // Get game instance
    Game *game = Game::GetInstance();

    if(game->GetEvent().type == SDL_KEYDOWN)
    {
        switch(game->GetEvent().key.keysym.sym)
        {
            case SDLK_LEFT:
            case SDLK_a:

                mGridX--;

                if(CheckPotentialCollision(landedGrid))
                {
                    // Undo last move
                    mGridX++;
                }

                if(mPlayingSounds)
                {
                    // Play movement sound
                    Mix_PlayChannel(-1, mMoveSound, 0);
                }

                break;

            case SDLK_RIGHT:
            case SDLK_d:

                mGridX++;

                if(CheckPotentialCollision(landedGrid))
                {
                    // Undo last move
                    mGridX--;
                }

                if(mPlayingSounds)
                {
                    // Play movement sound
                    Mix_PlayChannel(-1, mMoveSound, 0);
                }

                break;

            case SDLK_LCTRL:
            case SDLK_q:

                if(mType != BLOCK_TYPE_O)
                {
                    // Cycle through orientations
                    mOrientation--;

                    // Keep orientation in bounds
                    if(mOrientation < UP)
                    {
                        mOrientation = LEFT;
                    }

                    // Check if new orientation will collide
                    if(CheckPotentialCollision(landedGrid))
                    {
                        // Undo the last move if it will
                        mOrientation++;
                    }

                    // Keep orientation in bounds, cycling back around if undoing last move at highest orientation value
                    if(mOrientation > LEFT)
                    {
                        mOrientation = UP;
                    }


                    if(mPlayingSounds)
                    {
                        // Play movement sound
                        Mix_PlayChannel(-1, mRotationSound, 0);
                    }
                }

                break;

            case SDLK_UP:
            case SDLK_w:

                if(mType != BLOCK_TYPE_O)
                {
                    // Cycle through orientations
                    mOrientation++;

                    // Keep orientation in bounds
                    if(mOrientation > LEFT)
                    {
                        mOrientation = UP;
                    }

                    // Check if new orientation will collide
                    if(CheckPotentialCollision(landedGrid))
                    {
                        // Undo the last move if it will
                        mOrientation--;
                    }

                    // Keep orientation in bounds, cycling back around if undoing last move at lowest orientation value
                    if(mOrientation < UP)
                    {
                        mOrientation = LEFT;
                    }


                    if(mPlayingSounds)
                    {
                        // Play movement sound
                        Mix_PlayChannel(-1, mRotationSound, 0);
                    }
                }

                break;
        }
    }
}

void Block::UpdatePosition(int landedGrid[GRID_HEIGHT][GRID_WIDTH])
{
    if(!mLanded)
    { 
       // Make block fall by one row
       IncrementY();

       // If there wasn't a collision with a tile on the grid
       if(CheckPotentialCollision(landedGrid))
       {
           // Undo increment
           mGridY--;

           // Block has landed on another block
           mLanded = true;
       }

    }

}

void Block::CheckBounds(int gridX, int gridY, int landedGrid[GRID_HEIGHT][GRID_WIDTH])
{
    // If there wasn't a collision with a tile on the grid
    if(!CheckPotentialCollision(landedGrid))
    {
        mLanded = false;
    }

    // Get the grid's height
    int pixelGridHeight = (GRID_HEIGHT * TILE_HEIGHT);

    // Get the grid's width
    int pixelGridWidth = (gridX + (GRID_WIDTH * TILE_WIDTH) - TILE_WIDTH);

    // cycle through each tile in the block matrix
    for(int row = 0; row < mHeight; row++)
    {
        for(int column = 0; column < mWidth; column++)
        {
            if(mBlockMatrix[mOrientation][row][column] != TILE_BLANK)
            {
                // Get coordinates of current block in matrix
                int pixelX = gridX + (TILE_WIDTH * mGridX) + (TILE_WIDTH * column);
                int pixelY = gridY + (TILE_HEIGHT * mGridY) + (TILE_HEIGHT * row) - (HIDDEN_ROWS  * TILE_HEIGHT);

                // If the block has gone too far to the left
                if(pixelX < gridX)
                {
                    // Move it back in bounds
                    mGridX++;
                } 
                // If the block has gone too far to the right     
                else if(pixelX > pixelGridWidth)
                {
                    // Move it back in bounds
                    mGridX--;
                }

                // If any of the visible tiles in the shape are going below the board, stop it from going further
                if(pixelY == pixelGridHeight)
                {
                    mLanded = true;
                }
                else if(pixelY > pixelGridHeight)
                {
                    mGridY--;
                }
            }
        }
    }
}

bool Block::CheckPotentialCollision(int landedGrid[GRID_HEIGHT][GRID_WIDTH])
{
    // Update grid with landed block coords
    for(int row = 0; row < mHeight; row++)
    {
        for(int column = 0; column < mWidth; column++)
        {
            int srcY = row;
            int srcX = column;

            int dstY = mGridY + row - HIDDEN_ROWS;
            int dstX = mGridX + column;

                // If it isn't in a hidden row
                if(dstY > 0)
                {
                    // if the destination is not a blank tile
                    if(landedGrid[dstY][dstX] != TILE_BLANK)
                    {
                        // and the source is not a blank tile
                        if(mBlockMatrix[mOrientation][srcY][srcX] != TILE_BLANK)
                        {
                            return true;
                        }
                    }
                }
        }
    }

   return false;
}

void Block::Draw(int gridX, int gridY, int landedGrid[GRID_HEIGHT][GRID_WIDTH])
{
    // Get the grid's height
    int hiddenRowHeight = (HIDDEN_ROWS * TILE_HEIGHT);

    if(mShowGhost)
    {
        // Draw the ghost
        DrawGhost(gridX, gridY, landedGrid);
    }

    // Cycle through data
    for(int row = 0; row < mHeight; row++)
    {
        for(int column = 0; column < mWidth; column++)
        {
            if(mBlockMatrix[mOrientation][row][column] != TILE_BLANK)
            {
                // Get current tile's pixel coordinates
                int pixelX = gridX + (TILE_WIDTH * mGridX) + (TILE_WIDTH * column);
                int pixelY = gridY + (TILE_HEIGHT * mGridY) + (TILE_HEIGHT * row) - hiddenRowHeight;

                if( pixelY > hiddenRowHeight)
                {
                    mTexture->Draw(pixelX, pixelY);
                }                 
            }
        }
    }
}

void Block::DrawGhost(int gridX, int gridY, int landedGrid[GRID_HEIGHT][GRID_WIDTH])
{
    mGhostGridX = mGridX;
    mGhostGridY = mGridY;

    bool collided = false;

    while(!collided)
    {
        mGhostGridY++;

        // Update grid with landed block coords
        for(int row = 0; row < mHeight; row++)
        {
            for(int column = 0; column < mWidth; column++)
            {
                int srcY = row;
                int srcX = column;

                int dstY = mGhostGridY + row - HIDDEN_ROWS;
                int dstX = mGhostGridX + column;

                // If it isn't in a hidden row
                if(dstY > 0)
                {
                    // if the destination is not a blank tile
                    if(landedGrid[dstY][dstX] != TILE_BLANK)
                    {
                        // and the source is not a blank tile
                        if(mBlockMatrix[mOrientation][srcY][srcX] != TILE_BLANK)
                        {
                            collided = true;
                        }
                    }
                }
            }
        }

        if(collided == true)
        {
            mGhostGridY--;
        }
    }

    // Get the grid's height
    int hiddenRowHeight = (HIDDEN_ROWS * TILE_HEIGHT);

    for(int row = 0; row < mHeight; row++)
    {
        for(int column = 0; column < mWidth; column++)
        {
            if(mBlockMatrix[mOrientation][row][column] != TILE_BLANK)
            {
                // Get current tile's pixel coordinates
                int pixelX = gridX + (TILE_WIDTH * mGhostGridX) + (TILE_WIDTH * column);
                int pixelY = gridY + (TILE_HEIGHT * mGhostGridY) + (TILE_HEIGHT * row) - hiddenRowHeight;

                if(pixelY > hiddenRowHeight)
                {
                    mGhostTexture.Draw(pixelX, pixelY);
                }
            }
        }
    }
    
}