#include "CBoard.h"
#include "CoreGame.h"
#include "CInGameState.h"

Board::Board(int xPos, int yPos)
{
    // Grab game instance
    Game *game = Game::GetInstance();

    // Initialize variables
    mScore           = 0;
    mGameOver        = false;
    mLinesScored     = 0;
    mLevel           = 1;
    mSoftDropBonus   = 0;
    mSwappedRecently = false;

    mPlaySounds      = true;
    mShowGhost       = true;

    // Initialize line clear sound effect
    mLineClearSound = Mix_LoadWAV("Sounds/lineclear.wav");

    // Initialize text color
    mTextColor = {255, 255, 255};
    mTextColorMod = { 255, 255, 255 };

    // Initialize score text
    mScoreText.LoadText("Score: 0", mTextColor, game->GetDefaultFont());

    // Initialize next block text
    mNextBlockText.LoadText("Next Block:", mTextColor, game->GetDefaultFont());

    // Initialize held block text
    mHeldBlockText.LoadText("Holding:", mTextColor, game->GetDefaultFont());

    // Initialize lines cleared text
    mLinesClearedText.LoadText("Lines Cleared: 0", mTextColor, game->GetDefaultFont());

    // Initialize level text
    mLevelText.LoadText("Level: 1", mTextColor, game->GetDefaultFont());


    // Set position
    mXPos = xPos;
    mYPos = yPos;

    // Set clipping region
    mClipRect.x = xPos;
    mClipRect.y = yPos + (HIDDEN_ROWS * TILE_HEIGHT);
    mClipRect.w = GRID_WIDTH * TILE_WIDTH;
    mClipRect.h = (GRID_HEIGHT * TILE_HEIGHT) - (HIDDEN_ROWS * TILE_HEIGHT); 

    // Set modifiable delay
    mDelay = START_DELAY;

    // Current delay
    mModDelay = mDelay;

    // Grab currentTime
    mDelayCount = 0;

    // Load grid
    mGridTexture.LoadImage("Images/grid.png");

    // Load Tile textures
    mBlockTextures[TILE_CYAN].LoadImage(   "Images/tile_cyan.png"   );
    mBlockTextures[TILE_YELLOW].LoadImage( "Images/tile_yellow.png" );
    mBlockTextures[TILE_PURPLE].LoadImage( "Images/tile_purple.png" );
    mBlockTextures[TILE_GREEN].LoadImage(  "Images/tile_green.png"  );
    mBlockTextures[TILE_RED].LoadImage(    "Images/tile_red.png"    );
    mBlockTextures[TILE_BLUE].LoadImage(   "Images/tile_blue.png"   );
    mBlockTextures[TILE_ORANGE].LoadImage( "Images/tile_orange.png" );

    // Initialize grid matrix to 0's
    int row    = 0;
    int column = 0;

    for (row = 0; row < GRID_HEIGHT; row++)
    {
        for (column = 0; column < GRID_WIDTH; column++)
        {
            mLandedGrid[row][column] = TILE_BLANK;
        }
    }

    // Initialize border dimensions to be 1 pixel bigger than the grid itself
    mBorder = { mClipRect.x - 1, mClipRect.y - 1, mClipRect.w + 1, mClipRect.h + 2 };

    // Initialize border color to white
    mBorderClr = { 255, 255, 255 };

    // Generate block
    GenerateBlock();
}

Board::~Board()
{
    // Delete the line clear sound effect
    Mix_FreeChunk(mLineClearSound);

    // Set the pointer to null
    mLineClearSound = NULL;

    // Delete score texture
    mScoreText.Free();

    // Delete next block text
    mNextBlockText.Free();

    // Delete held block text
    mHeldBlockText.Free();

    // Delete lines cleared text
    mLinesClearedText.Free();

    // Delete level text
    mLevelText.Free();

    // Delete grid texture
    mGridTexture.Free();

    // Delete the current block
    delete mCurrentBlock;

    // Set pointer to null
    mCurrentBlock = NULL;

    // Delete the next block
    delete mNextBlock;

    // Set pointer to null
    mNextBlock = NULL;

    // Delete the held block
    delete mHeldBlock;

    // Set pointer to null
    mHeldBlock = NULL;
}

void Board::HandleEvents()
{
    // Get game instance
    Game *game = Game::GetInstance();

    // Handle currentBlocks events within gameboard
    mCurrentBlock->HandleEvents(mLandedGrid);

    // Check for keypresses
    if(game->GetEvent().type == SDL_KEYDOWN)
    {
        switch(game->GetEvent().key.keysym.sym)
        {
            case SDLK_DOWN:
            case SDLK_s:

                // Drop block faster
                mModDelay = SOFT_DROP_DELAY;

                break;

            case SDLK_SPACE:

                // Swap the held block
                SwapHeldBlock();

                break;

            case SDLK_F3:

                mPlaySounds = !mPlaySounds;

                // Toggle block sounds
                mCurrentBlock->PlaySounds(mPlaySounds);

                break;

            case SDLK_F4:

                mShowGhost = !mShowGhost;

                // Toggle ghost blocks
                mCurrentBlock->ShowGhost(mShowGhost); 

                break;
        }
    }
}

void Board::SwapHeldBlock()
{   
    // If there isn't a block being held
    if(mHeldBlock == NULL)
    {
        // Create a block to store the current block data with fixed orientation for display
        mHeldBlock = new Block(mCurrentBlock->GetType(), LEFT, &mBlockTextures[mCurrentBlock->GetType()]);

        // Don't show ghost or play sounds for held block
        mHeldBlock->ShowGhost(false);
        mHeldBlock->PlaySounds(false);

        // Generate the next block
        GenerateBlock();
    }

    // If there is a block being held
    else if(mHeldBlock != NULL)
    {
        if(!mSwappedRecently)
        {
            // Generate random orientation
            int orientation = (rand() % NUM_DIRECTIONS);

            // Generate a temporary block with the current block data with fixed orientation for display
            Block *temp = new Block(mCurrentBlock->GetType(), LEFT, &mBlockTextures[mCurrentBlock->GetType()]);

            // Delete the currentBlock data
            delete mCurrentBlock;

            // Swap the current and held blocks but with random orientation for current block
            mCurrentBlock = new Block(mHeldBlock->GetType(), orientation, &mBlockTextures[mHeldBlock->GetType()]);

            // Show ghosts and play sounds depending on bools
            mCurrentBlock->ShowGhost(mShowGhost);
            mCurrentBlock->PlaySounds(mPlaySounds);

            // Delete the held block
            delete mHeldBlock;

            // Set the new held block to be the old mCurrentBlock using temp data
            mHeldBlock = new Block(temp->GetType(), temp->GetDirection(), &mBlockTextures[temp->GetType()]);

            // Don't show ghost or play sounds for held block
            mHeldBlock->ShowGhost(false);
            mHeldBlock->PlaySounds(false);

            // Delete the temporary block
            delete temp;

            // Set recently swapped status
            mSwappedRecently = true;
        }
    }
}

void Board::SetTextColor(int r, int g, int b)
{
    // Set the text Color
    mScoreText.SetColor(r, g, b);

    // Set the next block text color
    mNextBlockText.SetColor(r, g, b);

    // Set the held block text color
    mHeldBlockText.SetColor(r, g, b);

    // Set the lines cleared text color
    mLinesClearedText.SetColor(r, g, b);

    // Set the level text color
    mLevelText.SetColor(r, g, b);

    // Set the color modulation
    mTextColorMod = {r, g, b};
}

void Board::UpdateHUD()
{
    // Grab the game instance
    Game *game = Game::GetInstance();

    // Store initial score
    int initialScore = mScore;

    // Create a stringstream to store score
    stringstream scoreSS;

    // Create a stringstream to store lines cleared
    stringstream linesSS;

    // Create a stringstream to store level
    stringstream levelSS;

    // Set score according to number of lines cleared in last line clear
    switch(mLinesScored)
    {
        case 1:
        mScore += 40 * (mLevel + 1) + mSoftDropBonus;
        break;

        case 2:
        mScore += 100 * (mLevel + 1) + mSoftDropBonus;
        break;

        case 3:
        mScore += 300 * (mLevel + 1) + mSoftDropBonus;
        break;

        case 4:
        mScore += 1200 * (mLevel + 1) + mSoftDropBonus;
        break;
    }    

    // This check prevents flickering

        // If the score changed
        if(mScore != initialScore)
        {
            // Update the stringstream with the current score
            scoreSS << "Score: " << mScore;

            // Free the current texture
            mScoreText.Free();

            // Load the current score as the texture
            mScoreText.LoadText(scoreSS.str(), mTextColor, game->GetDefaultFont());

            // Set the color modulation
            mScoreText.SetColor(mTextColorMod.r, mTextColorMod.g, mTextColorMod.b);

            // Update lines cleared text

                // Update the stringstream with the lines cleared
                linesSS << "Lines Cleared: " << mLinesCleared;

                // Free the current texture
                mLinesClearedText.Free();

                // Load the current number of lines cleared as the texture
                mLinesClearedText.LoadText(linesSS.str(), mTextColor, game->GetDefaultFont());

                // Set the color modulation
                mLinesClearedText.SetColor(mTextColorMod.r, mTextColorMod.g, mTextColorMod.b);

            // Update level text

                // Update the stringstream with the current level
                levelSS << "Level: " << mLevel;

                // Free the current texture
                mLevelText.Free();

                // Load the current level as the texture
                mLevelText.LoadText(levelSS.str(), mTextColor, game->GetDefaultFont());

                // Set the color modulation
                mLevelText.SetColor(mTextColorMod.r, mTextColorMod.g, mTextColorMod.b);
        }
}

void Board::Update()
{
    // Keep block in bounds
    mCurrentBlock->CheckBounds(mXPos, mYPos, mLandedGrid);

    // Get time
    int timeDifference = SDL_GetTicks() - mDelayCount;

    // Check if enough time has passed to update
    if(timeDifference >= mModDelay)
    {

        // Check if the block is being soft dropped
        if(mModDelay == SOFT_DROP_DELAY)
        {
            // Increment soft drop bonus
            mSoftDropBonus++;
        }

        // Update current block
        mCurrentBlock->UpdatePosition(mLandedGrid);

        // Reset timer
        mDelayCount = SDL_GetTicks();

        // If the current block has landed
        if(mCurrentBlock->HasLanded())
        {
            // Reset the hold swap status
            mSwappedRecently = false;

            // Reset the soft drop bonus
            mSoftDropBonus = 0;

            // Update grid with landed block coords
            for(int row = 0; row < mCurrentBlock->GetHeight(); row++)
            {
                for(int column = 0; column < mCurrentBlock->GetWidth(); column++)
                {
                    // Set source and destination indices
                    int srcY = row;
                    int srcX = column;

                    int dstY = mCurrentBlock->GetGridY() + row - HIDDEN_ROWS;
                    int dstX = mCurrentBlock->GetGridX() + column;

                    int direction = mCurrentBlock->GetDirection();
                   
                    // if the destination is a blank tile
                    if(mLandedGrid[dstY][dstX] == TILE_BLANK)
                    {
                        // and the source is not a blank tile
                        if(mCurrentBlock->GetBlockMatrix()[direction][srcY][srcX] != TILE_BLANK)
                        {
                           // Set the landed grid coordinate
                           mLandedGrid[dstY][dstX] = mCurrentBlock->GetBlockMatrix()[direction][srcY][srcX];
                        }
                    }

                    // If the tile's top left corner is in the hidden rows
                    if(dstY < HIDDEN_ROWS)
                    {
                        // The game is over
                        mGameOver = true;
                    }
                }
            }

            // Clear lines if necessary and update score
            ClearLines();

            // Level up every 10 lines
            mLevel = (mLinesCleared / 10) + 1;

            // Update delay
            mDelay = START_DELAY - (mLevel * DELAY_DECREMENT);

            // Update score
            UpdateHUD();

            // Reset number of lines scored
            mLinesScored = 0;

            // Generate block
            GenerateBlock();
        }
    }

    // Keep block in bounds
    mCurrentBlock->CheckBounds(mXPos, mYPos, mLandedGrid);

    // Reset delay
    mModDelay = mDelay;
}

void Board::Draw()
{
    // Get game instance
    Game *game = Game::GetInstance();

    // Draw the grid below the hidden rows
    mGridTexture.Draw(mXPos, mYPos + (HIDDEN_ROWS * TILE_HEIGHT));

    // Set border color and semi transparency for glowing effect
    SDL_SetRenderDrawColor(game->GetRenderer(), mBorderClr.r, mBorderClr.g, mBorderClr.b, 100);

    // Draw the border
    SDL_RenderDrawRect(game->GetRenderer(), &mBorder);

    // Draw landed blocks
    int row = 0;
    int column = 0;

    for (row = HIDDEN_ROWS; row < GRID_HEIGHT; row++)
    {
        for (column = 0; column < GRID_WIDTH; column++)
        {
            // If the tile isn't blank
            if (mLandedGrid[row][column] != TILE_BLANK)
            {
                // Grab the current id
                int curId = mLandedGrid[row][column];

                // Draw the correct texture over the grid at the specified cell
                mBlockTextures[curId].Draw(mXPos + (column * TILE_WIDTH), mYPos + (row * TILE_HEIGHT));
            }
        }
    }

    // Draw current block
    mCurrentBlock->Draw(mXPos, mYPos, mLandedGrid);

    // Draw the HUD
    DrawHUD();
}

void Board::DrawHUD()
{
    // Get game instance
    Game *game = Game::GetInstance();

    // Left side 
        // Draw the score text
        mScoreText.Draw((mXPos - mScoreText.GetWidth()) / 2, game->CenterY(mYPos) / 2);

        // Draw the lines cleared text
        mLinesClearedText.Draw((mXPos - mLinesClearedText.GetWidth()) / 2, game->CenterY(mYPos));

        // Draw the level text
        mLevelText.Draw((mXPos - mLevelText.GetWidth()) / 2, 3 * (game->CenterY(mYPos) / 2));


    // Right side

        // Draw next block Text
        mNextBlockText.Draw(game->GetScreenWidth() / 3 + (game->CenterX(mNextBlockText.GetWidth())), game->CenterY(mYPos) / 2);

        // Draw next block preview
        mNextBlock->Draw( game->GetScreenWidth() / 3 + (game->CenterX(mNextBlock->GetWidth() * TILE_WIDTH)), game->CenterY(mYPos + (mNextBlock->GetHeight() * TILE_HEIGHT)), mLandedGrid);

        // Draw held block Text
        mHeldBlockText.Draw(game->GetScreenWidth() / 3 + (game->CenterX(mHeldBlockText.GetWidth())), game->CenterY(mYPos) );

        // If a block is being held
        if(mHeldBlock != NULL)
        {
            // Draw held block preview
            mHeldBlock->Draw(game->GetScreenWidth() / 3 + (game->CenterX(mHeldBlock->GetWidth() * TILE_WIDTH)), game->CenterY(mYPos + (mHeldBlock->GetHeight() * TILE_HEIGHT)) + game->GetScreenHeight()/4, mLandedGrid);
        }   
}

void Board::GenerateBlock()
{
    // Delete the current block if necessary
    if(mCurrentBlock != NULL)
    {
        delete mCurrentBlock;
        mCurrentBlock =  NULL;
    }

    // Pick random block
    int type = (rand() % BLOCK_SHAPES) + 1;

    // Make lines spawn less often by rerolling 50/50 if it is a line
    if(type == BLOCK_TYPE_I)
    {
        // Set type to a random number
        int randNum = rand();

        // If the roll was odd
        if(randNum & 1)
        {
            // Spawn a line
            type = BLOCK_TYPE_I;
        }
        // otherwise If the roll was even
        else
        {
            // Spawn a random shape, potentially still be a line
            type = (rand() % BLOCK_SHAPES) + 1;
        }
    }

    // Random middle screen position
    int xPos = (rand() % (GRID_WIDTH / 2)) + 2;

    // Random orientation
    int orientation = (rand() % NUM_DIRECTIONS);

    // If this is the first block to be initialized
    if(mNextBlock == NULL)
    {
        // Pick random block
        int type = (rand() % BLOCK_SHAPES) + 1;

        // Make lines spawn less often by rerolling 50/50 if it is a line
        if(type == BLOCK_TYPE_I)
        {
            // Set type to a random number
            int randNum = rand();

            // If the roll was odd
            if(randNum & 1)
            {
                // Spawn a line
                type = BLOCK_TYPE_I;
            }
            // otherwise If the roll was even
            else
            {
                // Spawn a random shape, potentially still be a line
                type = (rand() % BLOCK_SHAPES) + 1;
            }
        }

        // Random middle screen position
        int xPos = (rand() % (GRID_WIDTH / 2)) + 2;

        // Random orientation
        int orientation = (rand() % NUM_DIRECTIONS);

        mCurrentBlock = new Block(type, orientation, &mBlockTextures[type]);
       
    }
    else
    {
        // Make a new block of the same type as the preview block but with a random direction
        mCurrentBlock = new Block(mNextBlock->GetType(), orientation, &mBlockTextures[mNextBlock->GetType()]);
    }

    // Set to center
    mCurrentBlock->SetGridX( xPos );
    mCurrentBlock->SetGridY( 0 );

    // Delete the next block if necessary
    if(mNextBlock != NULL)
    {
        delete mNextBlock;
        mNextBlock = NULL;
    }

    // Generate next block
    mNextBlock = new Block(type, LEFT, &mBlockTextures[type]);

    mCurrentBlock->ShowGhost(mShowGhost);
    mCurrentBlock->PlaySounds(mPlaySounds);

    mNextBlock->PlaySounds(false);
    mNextBlock->ShowGhost(false);
}

void Board::ClearLines()
{
    for(int row = 0; row < GRID_HEIGHT; row++)
    {
        // Each row is considered "filled" until a blank tile is found in it
        bool lineFilled = true;

        // Check each column in the row for a blank tile
        for(int column = 0; column < GRID_WIDTH; column++)
        {
            // If the tile is blank
            if(mLandedGrid[row][column] == TILE_BLANK)
            {
                // The line isn't filled
                lineFilled = false;
            }
        }

        // If none of the columns had a blank tile in the row
        // lineFilled will be true
        if(lineFilled)
        {
            // Go back through the columns and set each tile to blank, effectively removing the row
            for(int column = 0; column < GRID_WIDTH; column++)
            {
                if(row > HIDDEN_ROWS)
                {
                    mLandedGrid[row][column] = TILE_BLANK;
                }
            }

            // Increment number of lines scored
            mLinesScored++;

            // Increment total number of lines cleared
            mLinesCleared++;

            // Shift the blocks down
            ShiftBlocksDown(row);
        }
    }

    if(mLinesScored > 0)
    {
        // Play line clear sound
        Mix_PlayChannel(-1, mLineClearSound, 0);
    }
}

void Board::ShiftBlocksDown(int startRow)
{
    // Cycle backwards through rows
    for(int row = startRow; row > HIDDEN_ROWS; row--)
    {
        // Cycle through each column in row
        for(int column = 0; column < GRID_WIDTH; column++)
        {
            // Copy value from cell directly above it into the current row
            mLandedGrid[row][column] = mLandedGrid[row - 1][column];
        }
    }
}

bool Board::GameEnded()
{   
    // Return status
    return mGameOver;
}