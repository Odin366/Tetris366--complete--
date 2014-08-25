#include "CoreGame.h"
#include "CBoard.h"
#include "CBlock.h"

class InGameState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static InGameState *GetInstance()
    {
        if (inst == 0)
        {
            inst = new InGameState();
        }

        return inst;
    }


    /******************************/
    /* Place State functions here */

    SDL_Color GetCycleColor()
    {
        return cycleColor;
    }

    void SetCycleColor(int r, int g, int b)
    {
        SDL_Color color = {r, g, b};
        cycleColor = color;
    }

    int GetFinalScore()
    {
        return mScore;
    }

    /******************************/
private:

    static InGameState *inst;

    /**************************/
    /* Place State Items here */

    PSysMan* myPSysMan;

    Texture particle;
    Texture headerText;

    SDL_Color cycleColor;

    Board *gameBoard;

    Block *blockOne;

    int mScore;

    Mix_Music *mTheme;

    Mix_Chunk *mPauseSound;

    Mix_Chunk *mUnPauseSound;

    Mix_Chunk *mGameOverSound;

    /**************************/
};


