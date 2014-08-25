#include "CStartMenuState.h"
#include "CInGameState.h"
#include "CHighScoreState.h"
#include "CControlsState.h"
#include "Globals.h"

StartMenuState *StartMenuState::inst = 0;

void StartMenuState::Init()
{
    printf("Start menu Init\n");

    // Enable mouse
    SDL_ShowCursor(SDL_TRUE);

    // Initialize variables
    mAlphaVal = 0;
    mFadeSpeed = 4;
    mHaltSound = false;
   
    // Load the background image
    startBG.LoadImage("Images/startMenu.png");

    // Enable alpha blending
    startBG.SetBlendMode(SDL_BLENDMODE_BLEND);

    // Load the button
    startButton = new Button(0, 0, "  Start  ", 58);

    // Set the button placement
    startButton->SetX(game->CenterX(startButton->GetCollisionBox().w));
    startButton->SetY(game->CenterY(startButton->GetCollisionBox().h)); 

    // Load the high score button
    highScoresButton = new Button(0, 0, "  Highscores  ", 58);

    // Set the button placement
    highScoresButton->SetX(game->CenterX(highScoresButton->GetCollisionBox().w));
    highScoresButton->SetY(startButton->GetCollisionBox().y + 130);

    // Load the high score button
    controlsButton = new Button(0, 0, "  Controls  ", 58);

    // Set the button placement
    controlsButton->SetX(game->CenterX(controlsButton->GetCollisionBox().w));
    controlsButton->SetY(highScoresButton->GetCollisionBox().y + 130);


    // Load the button sound
    mButtonSound = Mix_LoadWAV("Sounds/buttonSound.wav");
}

void StartMenuState::Finalize()
{
    // Delete the button sound
    Mix_FreeChunk(mButtonSound);

    // Set the pointer to null
    mButtonSound = NULL;

    // Delete the background image
    startBG.Free();

    // Delete the first button
    delete startButton;

    // Set the pointer to null
    startButton = NULL;

    // Delete the second button
    delete highScoresButton;

    // Set the pointer to null
    highScoresButton = NULL;

    // Delete the second button
    delete controlsButton;

    // Set the pointer to null
    controlsButton = NULL;

    printf("Start menu Finalize\n\n");
}

void StartMenuState::Draw()
{
    // Clear the screen
    game->ClearScreen(0, 0, 0);

    // Set the background image alpha
    startBG.SetAlpha(mAlphaVal);

    // Draw the background
    startBG.Draw(game->CenterX(startBG.GetWidth()), game->CenterY(startBG.GetHeight()));

    // Set the first button alpha
    startButton->SetAlpha(mAlphaVal);

    // Draw the first button
    startButton->Draw();

    // Set the second button alpha
    highScoresButton->SetAlpha(mAlphaVal);

    // Draw the second button
    highScoresButton->Draw();

    // Set the second button alpha
    controlsButton->SetAlpha(mAlphaVal);

    // Draw the second button
    controlsButton->Draw();
}

void StartMenuState::Update()
{
    if(mAlphaVal < 255)
    {
        // Change alpha
        mAlphaVal += mFadeSpeed;
    }

    // Cap alpha
    if(mAlphaVal >= 255)
    {
        mAlphaVal = 255;
    }

    // Update buttons
    startButton->Update();
    highScoresButton->Update();
    controlsButton->Update();
}

void StartMenuState::HandleEvents()
{
    // If the screen has faded all the way in
    if(mAlphaVal == 255)
    {
        // Handle the first button's events
        startButton->HandleEvents();

        // Handle the second button's events
        highScoresButton->HandleEvents();

        // Handle the third button's events
        controlsButton->HandleEvents();
    }

    if((startButton->isMousedOver()) || (highScoresButton->isMousedOver()) || (controlsButton->isMousedOver()))
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


    // If the start button was pressed
    if(startButton->wasLeftReleased())
    {
        // Begin the game
        game->ChangeState(InGameState::GetInstance());
    }
    // If the highscores button was pressed
    else if(highScoresButton->wasLeftReleased())
    {
        // Take the user to the highscore screen 
        game->PushState(HighScoreState::GetInstance());
    }
    // If the controls button was pressed
    else if(controlsButton->wasLeftReleased())
    {
        // Take the user to the highscore screen 
        game->PushState(ControlsState::GetInstance());
    }
}

void StartMenuState::Pause()
{
    printf("Start menu Paused\n");
}
void StartMenuState::Resume()
{
    printf("Start menu Resumed\n");
}

