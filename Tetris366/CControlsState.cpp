#include "CControlsState.h"
#include "CStartMenuState.h"
#include "CInGameState.h"
#include "Globals.h"

ControlsState *ControlsState::inst = 0;

void ControlsState::Init()
{
    printf("High Score Init\n");

    // Initialize variables
    mHaltSound = false;

    // Initialize the button
    mBackButton = new Button(0, 0, " Back ", 48);

    mBackButton->SetX(game->GetScreenWidth() - mBackButton->GetCollisionBox().w - 30);
    mBackButton->SetY(game->GetScreenHeight() - mBackButton->GetCollisionBox().h - 30);

    // Open font
    mFont = TTF_OpenFont("Fonts/ClearSansMedium.ttf", 64);

    // Load header
    mBg.LoadImage("Images/controls.png");

    // Load the button sound
    mButtonSound = Mix_LoadWAV("Sounds/buttonSound.wav");
}

void ControlsState::Finalize()
{
    printf("High Score Finalize\n\n");

    // Delete the header
    mBg.Free();

    // Close the font
    TTF_CloseFont(mFont);

    // Delete the button
    delete mBackButton;

    // Set the pointer to null
    mBackButton = NULL;

    // Delete the button sound
    Mix_FreeChunk(mButtonSound);

    // Set the pointer to null
    mButtonSound = NULL;
}

void ControlsState::Draw()
{
    // Clear the screen
    game->ClearScreen(0, 0, 0);

    // Draw controls image
    mBg.Draw(0,0);   

    // Draw the button
    mBackButton->Draw();
}

void ControlsState::Update()
{
    mBackButton->Update();
}

void ControlsState::HandleEvents()
{
    mBackButton->HandleEvents();

    if(mBackButton->isMousedOver())
    {
        if(!mHaltSound)
        {
            Mix_PlayChannel(-1, mButtonSound, 0);
        }

        mHaltSound = true;
    }
    else
    {
        mHaltSound = false;
    }

    if(mBackButton->wasLeftReleased())
    {
        // Go back to main menu
        game->PopState();
    }
}

void ControlsState::Pause()
{
    printf("High Score Paused\n");
}
void ControlsState::Resume()
{
    printf("High Score Resumed\n");
}