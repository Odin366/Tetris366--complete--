#include "CIntroState.h"
#include "CStartMenuState.h"
#include "Globals.h"

IntroState *IntroState::inst = 0;

void IntroState::Init()
{
    printf("Intro Init\n");

    // Disable mouse
    SDL_ShowCursor(SDL_FALSE);
   
    // Initialize variables
    mAlphaVal  = 0;
    mFadeSpeed = 2;

    // Load intro texture
    avatarTexture.LoadImage("Images/name.png");

    // Enable Blending
    avatarTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void IntroState::Finalize()
{    
    printf("Intro Finalize\n\n");

    // Free the texture
    avatarTexture.Free();
}

void IntroState::Draw()
{
    // Clear the screen
    game->ClearScreen(0, 0, 0);

    // Set the alpha value of the image
    avatarTexture.SetAlpha(mAlphaVal);

    // Draw the texture
    avatarTexture.Draw(0, 0);
}

void IntroState::Update()
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
        game->ChangeState(StartMenuState::GetInstance());
    }
}

void IntroState::HandleEvents()
{
}

void IntroState::Pause()
{
    printf("Intro Paused\n");
}
void IntroState::Resume()
{
    printf("Intro Resumed\n");
}

