#include "CoreGame.h"

class StartMenuState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static StartMenuState *GetInstance()
    {
        if (inst == 0)
        {
            inst = new StartMenuState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static StartMenuState *inst;

    /**************************/
    /* Place State Items here */

    Texture startBG;

    Button *startButton;
    Button *highScoresButton;
    Button *controlsButton;

    int mAlphaVal;

    int mFadeSpeed;

    Mix_Chunk *mButtonSound;

    bool mHaltSound;

    /**************************/
};


