#include "CGameOverState.h"
#include "CEnterNameState.h"
#include "Globals.h"

GameOverState *GameOverState::inst = 0;

void GameOverState::Init()
{
    printf("Game Over Init\n");

    // Initialize variables
    mAlphaVal = 0;
    mFadeSpeed = 2;

    // Open game over font
    font = TTF_OpenFont("Fonts/ClearSansMedium.ttf", 60);

    // Load Game Over texture
    gameOverText.LoadText("GAME OVER", game->GetDefaultColor(), font);

    // Enable Blending
    gameOverText.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void GameOverState::Finalize()
{
    printf("Game Over Finalize\n\n");

    // Free the texture
    gameOverText.Free();

    // Delete the font
    TTF_CloseFont(font);

    // Set pointer to null
    font = NULL;
}

void GameOverState::Draw()
{
    // Clear the screen
    game->ClearScreen(0, 0, 0);

    // Set the alpha value of the image
    gameOverText.SetAlpha(mAlphaVal);

    // Draw the texture
    gameOverText.Draw(game->CenterX(gameOverText.GetWidth()), game->CenterY(gameOverText.GetHeight()));
}

void GameOverState::Update()
{
    // If the image faded all the way in
    if(mAlphaVal >= 255)
    {
        // Fade out
        mFadeSpeed = -mFadeSpeed;
    }

    // Change alpha
    mAlphaVal += mFadeSpeed;

    // Cap alpha
    if(mAlphaVal >= 255)
    {
        mAlphaVal = 255;
    }

    // If the alpha value went below 0
    if(mAlphaVal < 0)
    {
        // Begin the next state
        game->ChangeState(EnterNameState::GetInstance());
    }
}

void GameOverState::HandleEvents()
{
}

void GameOverState::Pause()
{
    printf("Game Over Paused\n");
}
void GameOverState::Resume()
{
    printf("Game Over Resumed\n");
}

