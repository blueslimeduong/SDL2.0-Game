#ifndef ENEMYOBJECT__H_
#define ENEMYOBJECT__H_

#include "commonfunc.h"
#include "BaseObject.h"
#include "BulletObject.h"
const int EFrame = 9;
const float ENEMY_SPEED = 4;
const int ENEMY_BULLET_SPEED = 5;
class EnemyObject : public BaseObject
{
public:
    EnemyObject();
    ~EnemyObject();

    enum TypeMove
    {
        STATIC_ENEMY = 0,
        MOVING_ENEMY = 1,
    };

    void set_x_val(const float& xVal){x_val_=xVal;}
    void set_y_val(const float& yVal){y_val_=yVal;}

    void set_x_pos(const float& xPos){x_pos_=xPos;}
    void set_y_pos(const float& yPos){y_pos_=yPos;}
    float get_x_pos()const{return x_pos_;}
    float get_y_pos()const{return y_pos_;}

    void set_clips();
    bool LoadImg(string path, SDL_Renderer* screen);
    void Show(SDL_Renderer* des);
    SDL_Rect GetRectFrame();
    int get_width_frame() const{return width_frame_;}
    int get_height_frame()const{return height_frame_;}
    void DoEnemy(Map& gMap);
    void CheckToMap(Map& map_data);

    void set_type_move(const int& typeMove){type_move_ = typeMove;}
    void change_dir_move();
    void UpdateImage(SDL_Renderer* des);
    void set_input_type_();
    vector<BulletObject*> get_bullet_list()const{return bullet_list_;}
    void set_bullet_list(const vector<BulletObject*> blist){bullet_list_ = blist;}

    void InitBullet(BulletObject* p_bullet, SDL_Renderer* screen);
    void MakeBullet(SDL_Renderer* screen,Map& map_data);
    void RemoveBullet(const int& index);
private:


    float x_pos_;
    float y_pos_;
    float x_val_;
    float y_val_;
//    int come_back_time_;
    SDL_Rect frame_clips_[EFrame];
    int width_frame_;
    int height_frame_;
    int frame_;

    int type_move_;
    Input input_type_;

    vector<BulletObject*> bullet_list_;

};
#endif // ENEMY_OBJECT__H_
