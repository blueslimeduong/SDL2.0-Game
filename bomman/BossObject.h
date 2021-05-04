#ifndef BOSSOBJECT__H_
#define BOSSOBJECT__H_

#include "commonfunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
#include "EnemyObject.h"

const int BFrame = 12;
const float BOSS_SPEED = 2;
const int BOSS_BULLET_SPEED = 6.5;
const int BOSS_MAX_Y = 544;
const int BOSS_MIN_Y = 224;

class BossObject: public BaseObject
{
public:
    BossObject();
    ~BossObject();
    void set_x_val(const float& xVal){x_val_=xVal;}
    void set_y_val(const float& yVal){y_val_=yVal;}

    void set_x_pos(const float& xPos){x_pos_=xPos;}
    void set_y_pos(const float& yPos){y_pos_=yPos;}
    float get_x_pos()const{return x_pos_;}
    float get_y_pos()const{return y_pos_;}

    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    SDL_Rect GetRectFrame();
    void DoEnemy(Map& gMap);
    void BossPosCheck();
    void CheckToMap(Map& map_data);
    vector<BulletObject*> get_bullet_list()const{return bullet_list_;}
    void set_bullet_list(const vector<BulletObject*> blist){bullet_list_ = blist;}

    void InitBullet(SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen,Map& map_data);
    void RemoveBullet(const int& index);

    void beAttacked() {life_point_ -= 2;}
    int get_boss_HP(){return life_point_;}
private:

    float x_pos_;
    float y_pos_;

    float x_val_;
    float y_val_;

    SDL_Rect frame_clips_[BFrame];
    int width_frame_;
    int height_frame_;
    int frame_;

    int life_point_;
    Input input_type_;

    vector<BulletObject*> bullet_list_;
};

#endif // BOSSOBJECT__H_
