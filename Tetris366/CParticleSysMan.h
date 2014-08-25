#pragma once

#include "CParticleSys.h"

class PSysMan // Particle Systems Manager
{
public:

    vector<ParticleSys *> systems;

    void HideSys(int sys);
    void ShowSys(int sys);

    void PushSys(int effect, Texture *texture, int levelWidth, int levelHeight);
    void PopSys();

    void KillEffects(); // kills all effects at once
    void ResEffects();  // ressurects all effects at once

    void Update();
    void Update(SDL_Rect *rect);

    void Draw();

    static PSysMan *GetInstance()
    {
        if (inst == 0)
        {
            inst = new PSysMan();
        }

        return inst;
    }

    void DestroyInstance()
    {
        delete inst;

        inst = 0;
    }

    bool IsActive()
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            if (systems[i]->isHidden()) // if any of the systems are hidden
            {
                return false;
            }
        }

        return true;
    }

    bool IsSysActive(int sys) // check for a specific sys
    {
        for (int i = 0; i < (int)systems.size(); i++)
        {
            if (systems[i]->GetType() == sys)
            {
                if (systems[i]->isHidden()) // if the chosen system is hidden
                {
                    return false;
                }
            }
        }

        return true;
    }

    void SetWidth(int newWidth)
    {
        maxSysWidth = newWidth;
    }

    void SetHeight(int newHeight)
    {
        maxSysHeight = newHeight;
    }

    int GetWidth()
    {
        return maxSysWidth;
    }

    int GetHeight()
    {
        return maxSysHeight;
    }

private:
    PSysMan();
    ~PSysMan();

    static PSysMan *inst;

    int maxSysWidth;
    int maxSysHeight;

};