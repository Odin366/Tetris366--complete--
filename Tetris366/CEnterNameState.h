#include "CoreGame.h"

class EnterNameState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    static EnterNameState *GetInstance()
    {
        if(inst == 0)
        {
            inst = new EnterNameState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static EnterNameState *inst;

    /**************************/
    /* Place State Items here */

    Texture mEnterNameTexture;
    Texture mInputTexture;

    bool mUpdateText;

    int mAlphaVal;

    int mFadeSpeed;

    string mInputText;

    TTF_Font *mFont;

    /**************************/
};


