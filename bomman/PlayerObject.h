#ifndef PLAYEROBJECT__H_
#define PLAYEROBJECT__H_

#include <vector>
#include "commonfunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
using namespace std;
const int Frame = 3;
const float PLAYER_MAX_SPEED = 4;
const int PLAYER_MAX_BULLET = 6;
const int BULLET_SPEED = 5.25;
const int MAX_LIFE_POINT = 3;
const int SPAWN_X = 32;
const int SPAWN_Y = 192;
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
    void HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* gFireball);

    void DoPlayer(Map& map_data, Mix_Chunk* Pick);
    void CheckToMap(Map& map_data, Mix_Chunk* Pick);
    void UpdateImagePlayer(SDL_Renderer* des);

    void set_bullet_list(vector<BulletObject*> bullet_list)
    {
        p_bullet_list_ = bullet_list;
    }
    vector<BulletObject*> get_bullet_list()const {return p_bullet_list_;}

    void HandleBullet(SDL_Renderer* des, Map &map_data, Mix_Chunk* Crate);
    void RemoveBullet(const int& index);

    int get_life_point(){return life_point_;}
    void IncreaseBullet();
    void IncreaseSpeed();
    void RefillLifePoint();

    SDL_Rect GetRectFrame();
    void respawn(Mix_Chunk* Die=NULL);
    void die(){life_point_--;}
    bool is_levelup(){return level_up;}
    bool set_level_up(const bool& lvup){level_up=lvup;}
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
    int life_point_;
    vector<BulletObject*> p_bullet_list_;
    int maxBullet_;

    float player_speed_;

    bool level_up;
};

#endif // PLAYEROBJECT__H_
