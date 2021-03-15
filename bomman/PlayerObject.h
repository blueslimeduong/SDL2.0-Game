#ifndef PLAYEROBJECT__H_
#define PLAYEROBJECT__H_

#include "commonfunc.h"
#include "BaseObject.h"
using namespace std;
const int Frame = 3;
const int PLAYER_SPEED = 5;
class PlayerObject : public BaseObject
{
public:
    PlayerObject();
    ~PlayerObject();

    enum WalkType
    {
        WALK_RIGHT = 0,
        WALK_LEFT  = 1,
        WALK_UP    = 2,
        WALK_DOWN  = 3,
    };

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen);
    void set_clips();

    void DoPlayer(Map& map_data);
    void CheckToMap(Map& map_data);
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clips_[Frame];//maybe 3

    Input input_type_;
    int frame_;
    int status_;
};

#endif // PLAYEROBJECT__H_
