#include "CHighScoreState.h"
#include "CStartMenuState.h"
#include "CInGameState.h"
#include "Globals.h"

HighScoreState *HighScoreState::inst = 0;

void HighScoreState::Init()
{
    printf("High Score Init\n");

    // Initialize variables
    mHaltSound = false;

    // Initialize the button
    mBackButton = new Button(0, 0, " Back ", 48);

    mBackButton->SetX(game->GetScreenWidth() - mBackButton->GetCollisionBox().w  - 30);
    mBackButton->SetY(game->GetScreenHeight() - mBackButton->GetCollisionBox().h - 30);

    // Open font
    mFont = TTF_OpenFont("Fonts/ClearSansMedium.ttf", 64);
    
    // Load header
    mHeader.LoadText("High Scores:", game->GetDefaultColor(), mFont);

    // Initialize variables
    ifstream file("Data/highscores.hsf");

    string name;
    int score;

    int count = 0;

    while(file >> name >> score)
    {
        mNames.push_back(name);
        mScores.push_back(score);
    }

    // If the list wasn't empty
    if(mScores.size() != 0)
    {  
       SortScores();
    }


    for(int score : mScores)
    {
        // Store line
        string scoreStr;
        string nameStr;

        // Increase count
        count++;

        if(count < 10)
        {
            // Create the line to be displayed
            nameStr  = "  " + to_string(count) + ".) " + mNames[count - 1] + " ";
            scoreStr = scoreStr + to_string(score);
        }
        else
        {
            // Create the line to be displayed
            nameStr =  to_string(count) + ".) " + mNames[count - 1] + " ";
            scoreStr = scoreStr + to_string(score);
        }

        // Push it onto the stack
        mHighScoreNames.push_back(new Texture());

        mHighScoreNames.back()->LoadText(nameStr, game->GetDefaultColor(), game->GetDefaultFont());

        mHighScoreTextures.push_back(new Texture());

        mHighScoreTextures.back()->LoadText(scoreStr, game->GetDefaultColor(), game->GetDefaultFont());
    }

    file.close();

    // Update list with scores
    ofstream out("Data/highscores.hsf");

    for(size_t i = 0; i < mScores.size(); i++)
    {
        out << mNames[i] << " " << mScores[i] << endl;
    }

    out.close();

    // Load the button sound
    mButtonSound = Mix_LoadWAV("Sounds/buttonSound.wav");    

    // Load empty list text
    mEmptyList.LoadText(" List is empty. No high scores have been set.", game->GetDefaultColor(), game->GetDefaultFont());
}

void HighScoreState::Finalize()
{
    printf("High Score Finalize\n\n");

    // Delete the header
    mHeader.Free();

    // Delete the empty list text
    mEmptyList.Free();

    // Close the font
    TTF_CloseFont(mFont);

    // Cycle through high score texture list
    for(Texture* line : mHighScoreNames)
    {
        // Delete each line
        delete line;

        // Pop the pointer off the stack
        mHighScoreNames.pop_back();
    }

    // Cycle through high score texture list
    for(Texture* line : mHighScoreTextures)
    {
        // Delete each line
        delete line;

        // Pop the pointer off the stack
        mHighScoreTextures.pop_back();
    }

    // Delete the button
    delete mBackButton;

    // Set the pointer to null
    mBackButton = NULL;

    // Delete the button sound
    Mix_FreeChunk(mButtonSound);

    // Set the pointer to null
    mButtonSound = NULL;  

    // Delete vector data
    for(int item : mScores)
    {
        mScores.pop_back();
    }

    for(string item : mNames)
    {
        mNames.pop_back();
    }
    
}

void HighScoreState::Draw()
{
    // Clear the screen
    game->ClearScreen(0, 0, 126);

    // Draw the button
    mBackButton->Draw();

    // Draw the header
    mHeader.Draw(game->CenterX(mHeader.GetWidth()), game->GetScreenHeight()/24);

    if(mScores.size() == 0)
    {
        mEmptyList.Draw(game->CenterX(mEmptyList.GetWidth()), game->CenterY(mEmptyList.GetHeight()));
    }
    else
    {
        int offset = mHeader.GetY() + mHeader.GetHeight();

        int count = 0;

        // Cycle through high score texture list
        for(Texture* name : mHighScoreNames)
        {
            // Increase offset
            offset += (game->GetScreenHeight() - mHeader.GetHeight()) / 16;

            // Draw the line
            name->Draw(game->CenterX(mHeader.GetWidth()) / 2, offset);

            count++;

            if(count == 10)
            {
                // Only show 10 high scores
                break;
            }
        }

        // Reset offset and count
        offset = mHeader.GetY() + mHeader.GetHeight();

        count = 0;

        for(Texture* score : mHighScoreTextures)
        {
            // Increase offset
            offset += (game->GetScreenHeight() - mHeader.GetHeight()) / 16;

            // Draw the line
            score->Draw(game->CenterX(mHeader.GetWidth()) * 2, offset);

            count++;

            if(count == 10)
            {
                // Only show 10 high scores
                break;
            }
        }
    }
}

void HighScoreState::Update()
{
   mBackButton->Update();
}

void HighScoreState::HandleEvents()
{
    mBackButton->HandleEvents();

    if( mBackButton->isMousedOver() )
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

void HighScoreState::Pause()
{
    printf("High Score Paused\n");
}
void HighScoreState::Resume()
{
    printf("High Score Resumed\n");
}

void HighScoreState::SortScores()
{
    // Init variables
    int index = 0;
    bool swapped = true;

    size_t length = mScores.size() - 1;

    // Continue until no swap has been made
    while(swapped)
    {
        // Set swapped to false
        swapped = false;

        size_t index;

        // Lop until second to last element in the array
        for( index = 0; index < length; index++)
        {
            // If the value at the index is greater than the value at index + 1
            if(mScores[index] > mScores[index + 1])
            {
                // Swap the items
                swap(mScores[index], mScores[index + 1]);

                // Swap the names at the same indices
                swap(mNames[index], mNames[index + 1]);

                // Set swapped to true
                swapped = true;
            }
        }
    }

    // Reverse the vectors
    reverse(mScores.begin(), mScores.end());
    reverse(mNames.begin(), mNames.end());
}