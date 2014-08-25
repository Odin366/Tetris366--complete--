#include "CPauseState.h"
#include "CStartMenuState.h"
#include "CInGameState.h"
#include "Globals.h"

PauseState *PauseState::inst = 0;

void PauseState::Init()
{
    printf("\tPause state Init\n");

    // Generate text
    description.LoadText("Game Paused", game->GetDefaultColor(), game->GetDefaultFont());
}

void PauseState::Finalize()
{
    // Delete text
    description.Free();

    printf("\tPause state Finalize\n\n");
}

void PauseState::Draw()
{
    // Render the description
    description.Draw(game->CenterX(description.GetWidth()), game->CenterY(description.GetHeight()));
}

void PauseState::Update()
{
}

void PauseState::HandleEvents()
{
    if (game->GetEvent().type == SDL_KEYDOWN)
    {
        switch (game->GetEvent().key.keysym.sym)
        {
        case SDLK_p:
            game->PopState();
            break;
        }
    }
}

void PauseState::Pause()
{
    printf("Pause state Paused\n");
}
void PauseState::Resume()
{
    printf("Pause state Resumed\n");
}

