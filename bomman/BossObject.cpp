#include "BossObject.h"

BossObject::BossObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
    frame_ = 0;
    life_point_ = 50;
    input_type_.left_=1;
    input_type_.right_=0;
    input_type_.down_=0;
    input_type_.up_=0;
}
BossObject::~BossObject()
{

}
bool BossObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if(ret)
    {
        width_frame_ = rect_.w/BFrame;
        height_frame_ = rect_.h;
        for(int i=0; i<BFrame; i++)
        {
            frame_clips_[i].x = i*width_frame_;
            frame_clips_[i].y = 0;
            frame_clips_[i].w = width_frame_;
            frame_clips_[i].h = height_frame_;
        }
        return true;
    }
    return false;
}
SDL_Rect BossObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.h = height_frame_;
    rect.w = width_frame_;
    return rect;
}
void BossObject::Show(SDL_Renderer* des)
{
    rect_.x = x_pos_ ;
    rect_.y = y_pos_ ;
    frame_++;
    if(frame_ >= BFrame)
    {
        frame_=0;
    }
    SDL_Rect* currentClips = &frame_clips_[frame_];
    SDL_Rect rendQuad = {rect_.x,rect_.y,width_frame_,height_frame_};
    SDL_RenderCopy(des,p_object_,currentClips,&rendQuad);

}
void BossObject::DoEnemy(Map& gMap)
{
        x_val_ = 0;
        y_val_ = 0;
        if(input_type_.left_==1)
        {
            x_val_ -= BOSS_SPEED;
        }
        else if(input_type_.right_==1)
        {
            x_val_ += BOSS_SPEED;
        }
        else if(input_type_.up_==1)
        {
            y_val_ -= BOSS_SPEED;
        }
        else if(input_type_.down_==1)
        {
            y_val_ += BOSS_SPEED;
        }
        CheckToMap(gMap);
}
void BossObject::BossPosCheck()
{
    if(input_type_.left_==1)
    {
        input_type_.left_ = 0;
        input_type_.right_ = 1;
    }
    else
    {
        input_type_.left_ = 1;
        input_type_.right_ = 0;
    }
}
void BossObject::CheckToMap(Map& map_data)
{
    int x1=0;
    int x2=0;

    int y1=0;
    int y2=0;

    //Kiem tra theo chieu ngang
    int height_min_ = height_frame_ < TILE_SIZE ? height_frame_ : TILE_SIZE;

    x1 = (x_pos_ + x_val_)/TILE_SIZE;
    x2 = (x_pos_ + x_val_ + width_frame_ - 1 )/TILE_SIZE;

    y1 = (y_pos_ )/TILE_SIZE;
    y2 = (y_pos_ + height_min_ - 1)/TILE_SIZE;

    if(x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if(x_val_ > 0)
        {
            int val1 = map_data.tile[y1][x2];
            int val2 =  map_data.tile[y2][x2];
            if((val1!=BLANK_TILE && val1<LIFE_TILE )||(val2!=BLANK_TILE && val2<LIFE_TILE ))
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;

                BossPosCheck();
            }
        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if((val1!=BLANK_TILE && val1<LIFE_TILE )||(val2!=BLANK_TILE && val2<LIFE_TILE ))
            {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_val_ = 0;

                BossPosCheck();
            }
        }
    }

    //Kiem tra theo chieu doc
    int width_min_ = width_frame_ < TILE_SIZE ? width_frame_ : TILE_SIZE;
    x1 = (x_pos_)/TILE_SIZE;
    x2 = (x_pos_ + width_min_ - 1)/TILE_SIZE;

    y1 = (y_pos_ + y_val_)/TILE_SIZE;
    y2 = (y_pos_ + y_val_ + height_frame_ - 1)/TILE_SIZE;

    if(x1>=0 && x2 < MAX_MAP_X && y1>=0 && y2 < MAX_MAP_Y)
    {
        if(y_val_>0)
        {
            int val1 = map_data.tile[y2][x1];
            int val2 = map_data.tile[y2][x2];
            if((val1!=BLANK_TILE && val1<LIFE_TILE )||(val2!=BLANK_TILE && val2<LIFE_TILE ))
            {
                y_pos_ = y2*TILE_SIZE;
                y_pos_ -= (height_frame_+1);
                y_val_ = 0;
            }
        }
        else if(y_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y1][x2];
            if((val1!=BLANK_TILE && val1<LIFE_TILE )||(val2!=BLANK_TILE && val2<LIFE_TILE ))
             {
                 y_pos_ =  (y1 + 1)*TILE_SIZE;
                 y_val_ = 0;
             }
        }
    }
    x_pos_ += x_val_;
    y_pos_ += y_val_;

}
void BossObject::InitBullet(SDL_Renderer* screen)
{   for(int i=0; i<3; i++)
    {
        BulletObject* p_bullet = new BulletObject();
        if(p_bullet!=NULL)
        {
            bool ret = p_bullet->LoadImg("img//bullet3.png",screen);
            p_bullet->set_is_move(true);
            p_bullet->set_bullet_dir(BulletObject::DIR_DOWN + i);
            if(input_type_.left_==1)
            {
                p_bullet->SetRect(rect_.x + width_frame_*0.2, rect_.y + height_frame_*0.5);
            }
            else
            {
                p_bullet->SetRect(rect_.x + width_frame_*0.7, rect_.y + height_frame_*0.5);
            }
            p_bullet->set_x_val(BOSS_BULLET_SPEED);
            p_bullet->set_y_val(BOSS_BULLET_SPEED);

            bullet_list_.push_back(p_bullet);
        }
    }
}
void BossObject::MakeBullet(SDL_Renderer* screen,Map& map_data)
{
    if(frame_==8)
    {
        InitBullet(screen);
    }
    for(int i=0; i<bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = bullet_list_[i];
        if(p_bullet!=NULL)
        {
            if(p_bullet->get_is_move())
            {
                p_bullet->HandleMove(map_data);
                p_bullet->Render(screen);
            }
            else
            {
                p_bullet->Free();
//                delete p_bullet;
                bullet_list_.erase(bullet_list_.begin() + i);
            }
        }
    }
}
void BossObject::RemoveBullet(const int& index)
{
    int size = bullet_list_.size();
    if(size>0 && index<size)
    {
        BulletObject* p_bullet = bullet_list_[index];
        bullet_list_.erase(bullet_list_.begin() + index);
    }
}
