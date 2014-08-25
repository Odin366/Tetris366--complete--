#include "CEnterNameState.h"
#include "CStartMenuState.h"
#include "CInGameState.h"
#include "Globals.h"

EnterNameState *EnterNameState::inst = 0;

void EnterNameState::Init()
{
    printf("Enter Name Init\n");

    // Initialize variables
    mAlphaVal = 0;
    mFadeSpeed = 2;
    mInputText = "Player";
    mUpdateText = false;

    // Open Enter Name Font
    mFont = TTF_OpenFont("Fonts/ClearSansMedium.ttf", 60);

    // Load input texture
    mInputTexture.LoadText(mInputText, game->GetDefaultColor(), mFont);

    // Load Enter Name texture
    mEnterNameTexture.LoadText("Enter your name:", game->GetDefaultColor(), mFont);

    // Enable Blending
    mEnterNameTexture.SetBlendMode(SDL_BLENDMODE_BLEND);
}

void EnterNameState::Finalize()
{
    printf("Enter Name Finalize\n\n");


    // Stop text input
    SDL_StopTextInput();

    // Free the enter name texture
    mEnterNameTexture.Free();

    // Free the input texture
    mInputTexture.Free();

    // Delete the Font
    TTF_CloseFont(mFont);

    // Set pointer to null
    mFont = NULL;
}

void EnterNameState::Draw()
{
    // Clear the screen
    game->ClearScreen(0, 0, 126);

    // Set the alpha value of the image
    mEnterNameTexture.SetAlpha(mAlphaVal);

    // Draw the texture
    mEnterNameTexture.Draw(game->CenterX(mEnterNameTexture.GetWidth()), (game->GetScreenHeight() - mEnterNameTexture.GetHeight())/4);

    // Set the alpha value of the image
    mInputTexture.SetAlpha(mAlphaVal);

    // Render the text
    mInputTexture.Draw(game->CenterX(mInputTexture.GetWidth()), game->CenterY(mInputTexture.GetHeight()));
}

void EnterNameState::Update()
{
    // Change alpha
    mAlphaVal += mFadeSpeed;

    // Cap alpha
    if(mAlphaVal >= 255)
    {
        mAlphaVal = 255;
    }

    // If completely faded in
    if(mAlphaVal == 255)
    {
        SDL_StartTextInput();
    }

    if(mUpdateText)
    {
        // If the text isn't empty
        if(mInputText != "")
        {
            // Render the new text
            mInputTexture.LoadText(mInputText.c_str(), game->GetDefaultColor(), mFont);
        }
        else
        {
            // Render a space
            mInputTexture.LoadText(" ", game->GetDefaultColor(), mFont);
        }
    }
}

void EnterNameState::HandleEvents()
{
    // If completely faded in
    if(mAlphaVal == 255)
    {
        if(game->GetEvent().type == SDL_KEYDOWN)
        {
            // Handle backspace
            if(game->GetEvent().key.keysym.sym == SDLK_BACKSPACE &&mInputText.length() > 0)
            {
                mInputText.pop_back();
                mUpdateText = true;
            }
            // Handle copy (ctrl + c)
            else if(game->GetEvent().key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL)
            {
                mInputText = SDL_SetClipboardText(mInputText.c_str());
            }
            // Handle paste (ctrl + v)
            else if(game->GetEvent().key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL)
            {
                mInputText = SDL_GetClipboardText();
                mUpdateText = true;
            }

            // If the enter key was pressed
            if(game->GetEvent().key.keysym.sym == SDLK_RETURN)
            {
                // Load highscore list
                ofstream out("Data/highscores.hsf", ios::app);

                    // Write the output line
                    out << mInputText << " " << InGameState::GetInstance()->GetFinalScore() << endl;
                
                // Close the file
                out.close();
                
                // Change the state
                game->ChangeState(StartMenuState::GetInstance());
                
            }

        }
        else if(game->GetEvent().type == SDL_TEXTINPUT)
        {
            // Not copying or pasting
            if(!((game->GetEvent().text.text[0] == 'c' || game->GetEvent().text.text[0] == 'C') && (game->GetEvent().text.text[0] == 'v' || game->GetEvent().text.text[0] == 'V') && SDL_GetModState() & KMOD_CTRL))
            {
                // Only upper case and lowercase letters allowed (no spaces, numbers, or punctuation)
                if(isupper(game->GetEvent().text.text[0]) || islower(game->GetEvent().text.text[0]))
                {
                    mInputText += game->GetEvent().text.text;

                    // Limit to 20 characters
                    if(mInputText.size() > 20)
                    {
                        mInputText.pop_back();
                    }

                    mUpdateText = true;
                }                
            }

        }
    }
}

void EnterNameState::Pause()
{
    printf("Enter Name Paused\n");
}
void EnterNameState::Resume()
{
    printf("Enter Name Resumed\n");
}