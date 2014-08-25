#include "CoreGame.h"

class ControlsState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static ControlsState *GetInstance()
    {
        if(inst == 0)
        {
            inst = new ControlsState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static ControlsState *inst;

    /**************************/
    /* Place State Items here */

    Texture mBg;

    TTF_Font *mFont;

    Button *mBackButton;

    Mix_Chunk *mButtonSound;

    bool mHaltSound;

    /**************************/
};


