#include "CParticleSys.h"

ParticleSys::ParticleSys(Texture *texture, int newEffect, int width, int height)
{
    effect = newEffect;

    sysWidth = width;
    sysHeight = height;

    hidden = false;

    sysColor = { 255, 255, 255 };

    InitEffect(texture, effect, sysWidth, sysHeight);

}
ParticleSys::~ParticleSys()
{
    if (effect != NONE)
    {
        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            delete particles[i];
            particles[i] = NULL;
        }
    }
}

void ParticleSys::Hide()
{
    for (int i = 0; i < TOTAL_PARTICLES; i++)
    {
        particles[i]->Kill();
    }

    if (!hidden)
    {
        hidden = true;
    }
}

void ParticleSys::Show()
{
    for (int i = 0; i < TOTAL_PARTICLES; i++)
    {
        particles[i]->Res();
    }

    if (hidden)
    {
        hidden = false;
    }
}

void ParticleSys::InitEffect(Texture *texture, int effect, int sysWidth, int sysHeight)
{
    int count = 0;

    switch (effect)
    {

    case STARFIELD:

        srand((unsigned int)time(NULL));

        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            particles[i] = new Particle(texture, (rand() % sysWidth), (rand() % sysHeight), rand() % 255);


            // Make the more transparent ( and therefore more distant ) stars move slower to appear farther away
            if (particles[i]->GetAlpha() > 175)
            {
                particles[i]->yVel = (rand() % 6) + 6; // 6 - 12 possible velocity for nearer stars
            }
            else if (particles[i]->GetAlpha() <= 175)
            {
                particles[i]->yVel = (rand() % 4) + 1;  // 1 - 4 possible velocity for distant stars
            }
        }
        break;

    case SNOW:

        srand((unsigned int)time(NULL));

        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            particles[i] = new Particle(texture, (rand() % sysWidth), (rand() % sysHeight), (rand() % 255));

            particles[i]->yVel = (rand() % 6) + 1; // 2 - 6 pixels per frame possible velocity

            particles[i]->SetTimer((rand() % 6) + 2); // DRIFT delay

        }
        break;
    }
}

void ParticleSys::DoEffect(int effect)
{
    switch (effect)
    {
    case STARFIELD:
        srand((unsigned int)time(NULL));

        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            if ((particles[i]->GetCollisionBox().x < 0) || (particles[i]->GetCollisionBox().y  > sysHeight) || (particles[i]->GetCollisionBox().x  > sysWidth))
            {
                particles[i]->SetY(-(rand() % (sysHeight / 8)) + 1);
            }
        }
        break;

    case SNOW:
        srand((unsigned int)time(NULL));

        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            if ((particles[i]->GetCollisionBox().x < 0) || (particles[i]->GetCollisionBox().y  > sysHeight) || (particles[i]->GetCollisionBox().x  > sysWidth))
            {
                particles[i]->SetY(-(rand() % (sysHeight / 8)) + 1);
                particles[i]->SetX((rand() % (sysWidth)) + 1);
            }

            double max = 2 * PI;
            double n = (rand() % ((int)max)) + 1;
            double a = cos(n);

            particles[i]->DecTimer();

            if (a > 0)
            {
                if (particles[i]->GetTimer() == 0)
                {
                    if (DRIFT != 0)
                    {
                        particles[i]->xVel = (rand() % (DRIFT + 1));
                    }
                    else
                    {
                        particles[i]->xVel = 0;
                    }

                    ;                    particles[i]->SetTimer((rand() % 6) + 2); // DRIFT delay
                }
            }
            else if (a <= 0)
            {
                if (particles[i]->GetTimer() == 0)
                {
                    if (DRIFT != 0)
                    {
                        particles[i]->xVel = -1 * ((rand() % (DRIFT + 1)));
                    }
                    else
                    {
                        particles[i]->xVel = 0;
                    }

                    particles[i]->SetTimer((rand() % 6) + 2); // DRIFT delay
                }
            }

        }
        break;
    }
}

void ParticleSys::Update()
{
    if (effect != NONE)
    {
        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            particles[i]->SetColor(sysColor);
            particles[i]->Update();
        }

        DoEffect(effect);
    }
}

void ParticleSys::ChangeEffect(Texture *texture, int newEffect)
{
    effect = newEffect;
    InitEffect(texture, newEffect, sysHeight, sysWidth);
}

void ParticleSys::Draw()
{
    if (effect != NONE)
    {
        for (int i = 0; i < TOTAL_PARTICLES; i++)
        {
            particles[i]->Draw();
        }
    }
}

void ParticleSys::SetSysColor(SDL_Color color)
{
    sysColor = color;
}