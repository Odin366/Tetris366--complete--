#include "CoreGame.h"

class GameOverState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static GameOverState *GetInstance()
    {
        if(inst == 0)
        {
            inst = new GameOverState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static GameOverState *inst;

    /**************************/
    /* Place State Items here */

    Texture gameOverText;

    int mAlphaVal;

    int mFadeSpeed;

    TTF_Font *font;

    /**************************/
};


