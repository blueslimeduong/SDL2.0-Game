#ifndef PLAYEROBJECT__H_
#define PLAYEROBJECT__H_

#include <vector>
#include "commonfunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
using namespace std;
const int Frame = 3;
const int PLAYER_SPEED = 3;
const int BULLET_SPEED = 6;
const int MAX_AMMO = 5;
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
    void UpdateImagePlayer(SDL_Renderer* des);

    void set_bullet_list(vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    vector<BulletObject*> get_bullet_list()const {return p_bullet_list_;}

    void HandleBullet(SDL_Renderer* des);
private:
    float x_val_;
    float y_val_;

    float x_pos_;
    float y_pos_;

    int width_frame_;
    int height_frame_;

    SDL_Rect frame_clips_[Frame];

    Input input_type_;
    int frame_;
    int status_;

    vector<BulletObject*> p_bullet_list_;
};

#endif // PLAYEROBJECT__H_
