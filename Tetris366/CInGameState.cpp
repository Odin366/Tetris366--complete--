#include "CInGameState.h"
#include "CPauseState.h"
#include "CGameOverState.h"
#include "Globals.h"

InGameState *InGameState::inst = 0;

void InGameState::Init()
{
    printf("In game Init\n");

    // Disable mouse
    SDL_ShowCursor(SDL_FALSE);

    // Initialize variables
    cycleColor = { 0, 100, 255 };

    // Load board texture
    gameBoard = new Board(game->CenterX( (GRID_WIDTH * TILE_WIDTH) ), game->CenterY( (GRID_HEIGHT * TILE_HEIGHT) ) );

    // Load particle system manager
    myPSysMan = PSysMan::GetInstance();

    // Load particle
    particle.LoadImage("Particle/particle.png");

    // Load particle system
    myPSysMan->PushSys(SNOW, &particle, game->GetScreenWidth(), game->GetScreenHeight());

    // Load title
    headerText.LoadText("Tetris 366", game->GetDefaultColor(), game->GetDefaultFont());

    // Load theme music
    mTheme = Mix_LoadMUS("Sounds/theme.wav");

    // Load the pause sound
    mPauseSound = Mix_LoadWAV("Sounds/pause.wav");

    // Load the unpause sound
    mUnPauseSound = Mix_LoadWAV("Sounds/unpause.wav");

    // Load the game over sound
    mGameOverSound= Mix_LoadWAV("Sounds/gameover.wav");

    // Play the music
    Mix_PlayMusic(mTheme, -1);
}

void InGameState::Finalize()
{
    // Delete the sound
    Mix_FreeChunk(mGameOverSound);

    // Set the pointer to null
    mGameOverSound = NULL;

    // Grab and retain the final score
    mScore = gameBoard->GetScore();

    // Delete particle system manager
    myPSysMan->DestroyInstance();

    // Delete Game board
    delete gameBoard;

    // Set pointer to null
    gameBoard = NULL;

    // Delete the block
    delete blockOne;

    // Set pointer to null
    blockOne = NULL;

    // Delete text
    headerText.Free();

    // Delete the particle texture
    particle.Free();    

    // Delete the music
    Mix_FreeMusic(mTheme);

    // Set the pointer to null
    mTheme = NULL;

    // Delete the pause sound
    Mix_FreeChunk(mPauseSound);

    // Set the pointer to null
    mPauseSound = NULL;

    // Delete the pause sound
    Mix_FreeChunk(mUnPauseSound);

    // Set the pointer to null
    mUnPauseSound = NULL;

    printf("In game Finalize\n\n");
}

void InGameState::Draw()
{
    // Clear screen
    game->ClearScreen(0, 0, 0);

    // Draw particles
    myPSysMan->Draw();

    // Draw gameboard
    gameBoard->Draw();

    // Draw header text
    headerText.Draw(game->CenterX(headerText.GetWidth()), gameBoard->GetYPos() / 2);

}

void InGameState::Update()
{
    // Progress color every few levels to represent difficulty increase
    if(gameBoard->GetLevel() < 2)
    {
        // Set the color to blue
        cycleColor = {0, 0, 255};
    }
    else if((gameBoard->GetLevel() >= 2) && (gameBoard->GetLevel() < 4))
    {
        // Set the color to green
        cycleColor = { 0, 255, 0 };
    }
    else if((gameBoard->GetLevel() >= 4) && (gameBoard->GetLevel() < 6))
    {
        // Set the color to purple
        cycleColor = { 255, 0, 255 };
    }
    else if((gameBoard->GetLevel() >= 6) && (gameBoard->GetLevel() < 9))
    {
        // Set the color to yellow
        cycleColor = { 255, 255, 0 };
    }
    else if((gameBoard->GetLevel() >= 9) && (gameBoard->GetLevel() < 12))
    {
        // Set the color to orange
        cycleColor = { 255, 127, 0 };
    }
    else if (gameBoard->GetLevel() >= 12)
    {
        // Set the color to red
        cycleColor = { 255, 0, 0 };
    }

    // Set particle colors to most recent cycled color
    myPSysMan->systems.back()->SetSysColor(cycleColor);

    // Update particles
    myPSysMan->Update();

    // Set gameboard border color
    gameBoard->SetBorderColor(cycleColor);

    // Set header color
    headerText.SetColor(cycleColor.r, cycleColor.g, cycleColor.b);

    // Pass the color to the gameboard to draw score
    gameBoard->SetTextColor(cycleColor.r, cycleColor.g, cycleColor.b);

    // If the game isn't over
    if(gameBoard->GameEnded() == false)
    {
        // Update gameboard
        gameBoard->Update();
    }
    else
    {
        // Stop the music
        Mix_HaltMusic();

        // Play the game over sound
        Mix_PlayChannel(-1, mGameOverSound, 0);

        // Delay for 3 second
        SDL_Delay(3000);

        // Change the state to the game over state
        game->ChangeState(GameOverState::GetInstance());
    }
}

void InGameState::HandleEvents()
{
    if (game->GetEvent().type == SDL_KEYDOWN)
    {
        // Handle gameboard events
        gameBoard->HandleEvents();

        switch (game->GetEvent().key.keysym.sym)
        {
        case SDLK_p:

            game->PushState(PauseState::GetInstance());

            break;

        case SDLK_F1:

            if(Mix_PlayingMusic() == 0)
            { 
                // Play the music if not playing already
                Mix_PlayMusic(mTheme, -1);
            }
            else
            {
                if(Mix_PausedMusic() == 1)
                {
                    // Resume if paused
                    Mix_ResumeMusic();
                }
                else
                {
                    // Pause if playing
                    Mix_PauseMusic();
                }
            }

            break;

        case SDLK_F2:

            // Stop the music
            Mix_HaltMusic();

            break;
        }
    }
}

void InGameState::Pause()
{
    // Play the pause sound
    Mix_PlayChannel(-1, mPauseSound, 0);

    // Pause the music
    Mix_PauseMusic();

    printf("In game Paused\n\n");
}
void InGameState::Resume()
{
    // Play the unpause sound
    Mix_PlayChannel(-1, mUnPauseSound, 0);

    // Minor delay to let the unpause sound play
    SDL_Delay(300);

    // Pause the music
    Mix_ResumeMusic();

    printf("In game Resumed\n\n");
}

