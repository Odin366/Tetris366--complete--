#pragma once

#include "Globals.h"

class Particle
{
public:
    Particle(Texture *texture, int x, int y, int newAlpha);
    ~Particle();

    void Update();
    void Draw();

    SDL_Color GetColor()
    {
        return color;
    }

    void SetColor(SDL_Color newColor)
    {
        color = newColor;
    }

    void SetX(int x)
    {
        collisionBox.x = x;
    }

    void SetY(int y)
    {
        collisionBox.y = y;
    }

    int xVel;
    int yVel;

    SDL_Rect GetCollisionBox()
    {
        return collisionBox;
    }

    bool isAlive()
    {
        return alive;
    }

    void Kill()
    {
        if (alive == true)
        {
            alive = false;
        }
    }

    void Res() // ressurect 
    {
        if (alive == false)
        {
            alive = true;
        }
    }

    int GetTimer()
    {
        return timer;
    }

    void DecTimer()
    {
        timer--;
    }

    void incTimer()
    {
        timer++;
    }

    void SetTimer(int newTime)
    {
        timer = newTime;
    }

    Texture* GetTexture()
    {
        return mTexture;
    }

    int GetAlpha()
    {
        return alpha;
    }

    void SetAlpha(int newAlpha)
    {
        alpha = newAlpha;
    }

    int GetAngle()
    {
        return angle;
    }

    void SetAngle(int newAngle)
    {
        angle = newAngle;
    }

private:

    bool alive;

    int alpha;

    int timer;

    SDL_Rect collisionBox;

    Texture* mTexture;

    SDL_Color color;

    int angle;
    
};