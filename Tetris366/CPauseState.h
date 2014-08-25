#include "CoreGame.h"

class PauseState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static PauseState *GetInstance()
    {
        if (inst == 0)
        {
            inst = new PauseState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static PauseState *inst;

    /**************************/
    /* Place State Items here */

    // Description text
    Texture description;

    /**************************/
};


