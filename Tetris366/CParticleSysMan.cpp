#include "CParticleSysMan.h"
#include "CoreGame.h"

PSysMan *PSysMan::inst = 0;

PSysMan::PSysMan()
{
    // Get game instance
    Game *game = Game::GetInstance();

    maxSysWidth =  game->GetScreenWidth();
    maxSysHeight = game->GetScreenHeight();
}

PSysMan::~PSysMan()
{
    if (!systems.empty())
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            systems.pop_back();
        }
    }
}

void PSysMan::PushSys(int effect, Texture *texture, int levelWidth, int levelHeight)
{
    ParticleSys *pSys = new ParticleSys(texture, effect, maxSysWidth, maxSysHeight);
    systems.push_back(pSys);
}

void PSysMan::PopSys()
{
    delete systems.back();
    systems.pop_back();
}

void PSysMan::HideSys(int sys)
{
    for (int i = 0; i < (int)systems.size(); i++)
    {
        if (systems[i]->GetType() == sys)
        {
            systems[i]->Hide();
            break;
        }
    }
}

void PSysMan::ShowSys(int sys)
{
    for (int i = 0; i < (int)systems.size(); i++)
    {
        if (systems[i]->GetType() == sys)
        {
            systems[i]->Show();
            break;
        }
    }
}

void PSysMan::KillEffects() // change to set effects to dead
{
    if (!systems.empty())
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            systems[i]->Hide();
        }
    }
}

void PSysMan::ResEffects() // change to set effects to dead
{
    if (!systems.empty())
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            systems[i]->Show();
        }
    }
}

void PSysMan::Update()
{
    if (!systems.empty())
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            if (systems[i]->GetWidth() != maxSysWidth)
            {
                systems[i]->SetWidth(maxSysWidth);
            }

            if (systems[i]->GetHeight() != maxSysHeight)
            {
                systems[i]->SetHeight(maxSysHeight);
            }

            systems[i]->Update();
        }
    }
}

void PSysMan::Draw()
{
    if (!systems.empty())
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            systems[i]->Draw();
        }
    }
}