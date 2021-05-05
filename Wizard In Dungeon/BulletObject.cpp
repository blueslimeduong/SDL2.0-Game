
#include "BulletObject.h"
using namespace std;

BulletObject::BulletObject()
{
    x_val_ = 0;
    y_val_ = 0;
    is_move_ = false;
}

BulletObject::~BulletObject()
{

}

void BulletObject::HandleMove(Map &map_data, Mix_Chunk* Crate)
{

    if(bullet_dir_==DIR_RIGHT)
    {
        rect_.x += x_val_;
    }
    else if(bullet_dir_==DIR_LEFT)
    {
        rect_.x -= x_val_;
    }
    else if(bullet_dir_==DIR_UP)
    {
        rect_.y -= y_val_;
    }
    else if(bullet_dir_ == DIR_DOWN)
    {
        rect_.y += y_val_;
    }
    else if(bullet_dir_ == DIR_UP_LEFT)
    {
        rect_.x -= x_val_;
        rect_.y -= y_val_;
    }
    else if(bullet_dir_ == DIR_UP_RIGHT)
    {
        rect_.x += x_val_;
        rect_.y -= y_val_;
    }
    else if(bullet_dir_ == DIR_DOWN_LEFT)
    {
        rect_.x -= x_val_;
        rect_.y += y_val_;
    }
    else if(bullet_dir_ == DIR_DOWN_RIGHT)
    {
        rect_.x += x_val_;
        rect_.y += y_val_;
    }
    CheckToMap(map_data,Crate);
}
void BulletObject::CheckToMap(Map &map_data, Mix_Chunk* Crate)
{
    int x = 0;
    int y = 0;
    if(bullet_dir_==DIR_RIGHT)
    {
        x = (rect_.x + rect_.w)/TILE_SIZE;
    }
    else
    {
        x = rect_.x/TILE_SIZE;
    }
    if(bullet_dir_==DIR_DOWN)
    {
        y = (rect_.y + rect_.h)/TILE_SIZE;
    }
    else
    {
        y = rect_.y/TILE_SIZE;
    }

    if(map_data.tile[y][x]>=BREAKABLE_TILE && map_data.tile[y][x]<LIFE_TILE)
    {
        Mix_PlayChannel(-1,Crate,0);
        ChangeBrokenBlock(map_data, x, y);
        is_move_ = false;
    }
    else if(map_data.tile[y][x] != BLANK_TILE)
    {
        is_move_ = false;
    }
}
void BulletObject::ChangeBrokenBlock(Map& map_data, const int& x, const int& y)
{
    int randVal = rand()%100 + 1;
    if(randVal<=5)
    {
        map_data.tile[y][x] = LIFE_TILE;
    }
    else if(randVal<=15)
    {
        map_data.tile[y][x] = SPEED_TILE;
    }
    else if(randVal<=25)
    {
        map_data.tile[y][x] = BULLET_TILE;
    }
    else
    {
        map_data.tile[y][x] = 0;
    }
    return;
}
