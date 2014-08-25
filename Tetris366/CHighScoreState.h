#include "CoreGame.h"

class HighScoreState : public GameState
{
public:
    void Init();
    void Finalize();

    void Pause();
    void Resume();

    void Draw();
    void HandleEvents();
    void Update();

    void SortScores();

    static HighScoreState *GetInstance()
    {
        if(inst == 0)
        {
            inst = new HighScoreState();
        }

        return inst;
    }

    /******************************/
    /* Place State functions here */
    /******************************/

private:

    static HighScoreState *inst;

    /**************************/
    /* Place State Items here */

    vector<Texture *> mHighScoreTextures;
    vector<Texture *> mHighScoreNames;

    Texture mHeader;
    Texture mEmptyList;

    TTF_Font *mFont;

    vector<int> mScores;
    vector<string> mNames;

    Button *mBackButton;

    Mix_Chunk *mButtonSound;

    bool mHaltSound;

    /**************************/
};


