#include "CParticle.h"

Particle::Particle(Texture *texture, int x, int y, int newAlpha)
{
    mTexture = texture;

    // Enable alpha blending
    mTexture->SetBlendMode(SDL_BLENDMODE_BLEND);

    collisionBox.x = x;
    collisionBox.y = y;
    collisionBox.w = mTexture->GetWidth();
    collisionBox.h = mTexture->GetHeight();
    xVel = 0;
    yVel = 0;

    alpha = newAlpha;

    alive = true;

    timer = 0;

    color = { 255, 255, 255 };

    angle = (rand() % 360);
}

Particle::~Particle()
{
    mTexture->Free();
}

void Particle::Update()
{
    if (alive)
    {
        angle += 20;

        if (angle > 360)
        {
            angle = 0;
        }
        collisionBox.x += xVel;
        collisionBox.y += yVel;
    }
}

void Particle::Draw()
{
    if (alive)
    {
        mTexture->SetAlpha(alpha);
        mTexture->SetColor(color.r, color.g, color.b);
        mTexture->Draw(collisionBox.x, collisionBox.y, NULL, angle);
    }
}