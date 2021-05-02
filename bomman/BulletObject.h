#ifndef BULLETOBJECT__H_
#define BULLETOBJECT__H_

#include "commonfunc.h"
#include "BaseObject.h"
#include "map.h"
class BulletObject :public BaseObject
{
public:
    BulletObject();
    ~BulletObject();

    enum BulletDir
    {
        DIR_RIGHT = 20,
        DIR_LEFT = 21,
        DIR_UP = 22,
        DIR_DOWN = 23,
    };

    void set_x_val(const int& xVal){x_val_ = xVal;}
    void set_y_val(const int& yVal){y_val_ = yVal;}
    int get_x_val() const {return x_val_;}
    int get_y_val() const {return y_val_;}

    void set_is_move(const bool& isMove){is_move_ = isMove;}
    bool get_is_move() const {return is_move_;}

    void set_bullet_dir(const unsigned int& bulletDir) {bullet_dir_ = bulletDir;}
    int get_bullet_dir(){return bullet_dir_;}
    void HandleMove(Map &map_data, Mix_Chunk* Crate = NULL);
    void CheckToMap(Map &map_data,Mix_Chunk* Crate = NULL);
    void ChangeBrokenBlock(Map& map_data, const int& x, const int& y);
private:
    int x_val_;
    int y_val_;
    bool is_move_;
    unsigned int bullet_dir_;

};

#endif // BULLETOBJECT__H_
