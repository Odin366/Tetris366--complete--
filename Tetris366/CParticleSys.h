#pragma once

#include "CParticle.h"

class ParticleSys
{
public:

    void Update();
    void Draw();

    void ChangeEffect(Texture *texture, int newEffect);

    void Hide();
    void Show();

    void InitEffect(Texture *texture, int newEffect, int width, int height);
    void DoEffect(int effect);

    void SetSysColor(SDL_Color color);

    int GetType()
    {
        return effect;
    }

    bool isHidden()
    {
        return hidden;
    }

    int maxSpeed; // particle speed

    ParticleSys(Texture *texture, int newEffect, int width, int height);
    ~ParticleSys();
    
    int GetWidth()
    {
        return sysWidth;
    }

    int GetHeight()
    {
        return sysHeight;
    }

    void SetWidth(int newWidth)
    {
        sysWidth = newWidth;
    }

    void SetHeight(int newHeight)
    {
        sysHeight = newHeight;
    }

private:

    Particle *particles[TOTAL_PARTICLES];

    int sysWidth;
    int sysHeight;

    int effect;

    bool hidden;

    SDL_Color sysColor;
};
