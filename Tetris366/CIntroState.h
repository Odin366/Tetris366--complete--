#include "CoreGame.h"

class IntroState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static IntroState *GetInstance()
    {
        if (inst == 0)
        {
            inst = new IntroState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static IntroState *inst;

    /**************************/
    /* Place State Items here */

    Texture avatarTexture;

    int mAlphaVal;

    int mFadeSpeed;

    /**************************/
};


