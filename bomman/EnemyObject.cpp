#include "EnemyObject.h"

EnemyObject::EnemyObject()
{
    width_frame_ = 0;
    height_frame_ = 0;
    x_val_ = 0;
    y_val_ = 0;
    x_pos_ = 0;
    y_pos_ = 0;
//    come_back_time_ = 0;
    frame_ = 0;
    type_move_ = STATIC_ENEMY;
    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.down_=0;
    input_type_.up_=0;
}

EnemyObject::~EnemyObject()
{

}

bool EnemyObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if(ret)
    {
        width_frame_ = rect_.w/EFrame;
        height_frame_ = rect_.h;
    }
}
SDL_Rect EnemyObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.h = height_frame_;
    rect.w = width_frame_;
    return rect;
}

void EnemyObject::set_clips()
{
    if(width_frame_ > 0 && height_frame_ > 0)
    {
        for(int i=0; i<EFrame; i++)
        {
            frame_clips_[i].x = i*width_frame_;
            frame_clips_[i].y = 0;
            frame_clips_[i].w = width_frame_;
            frame_clips_[i].h = height_frame_;
        }
    }
}

void EnemyObject::Show(SDL_Renderer* des)
{
    UpdateImage(des);
//    if(come_back_time_ == 0)
//    {
//        rect_.x = x_pos_ - map_x_;
//        rect_.y = y_pos_ - map_y_;
    rect_.x = x_pos_ ;
    rect_.y = y_pos_ ;
    frame_++;
    if(frame_>=EFrame)
    {
        frame_=0;
    }
    SDL_Rect* currentClips = &frame_clips_[frame_];
    SDL_Rect rendQuad = {rect_.x,rect_.y,width_frame_,height_frame_};
    SDL_RenderCopy(des,p_object_,currentClips,&rendQuad);
//    }
}
void EnemyObject::DoEnemy(Map& gMap)
{
//    if(come_back_time_ == 0)
//    {
        x_val_ = 0;
        y_val_ = 0;
        if(input_type_.left_==1)
        {
            x_val_ -= ENEMY_SPEED;
        }
        else if(input_type_.right_==1)
        {
            x_val_ += ENEMY_SPEED;
        }
        else if(input_type_.up_==1)
        {
            y_val_ -= ENEMY_SPEED;
        }
        else if(input_type_.down_==1)
        {
            y_val_ += ENEMY_SPEED;
        }
        CheckToMap(gMap);
//    }
//
//    else if(come_back_time_>0)
//    {
//        come_back_time_--;
//        if(come_back_time_==0)
//        {
//            x_val_ = 0;
//            y_val_ = 0;
//
//        }
//    }
}
void EnemyObject::CheckToMap(Map& map_data)
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
                if(type_move_==MOVING_ENEMY)
                {
                    change_dir_move();
                }
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
                if(type_move_==MOVING_ENEMY)
                {
                    change_dir_move();
                }
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
                if(type_move_==MOVING_ENEMY)
                {
                    change_dir_move();
                }
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
                if(type_move_==MOVING_ENEMY)
                {
                    change_dir_move();
                }
             }
        }
    }
    x_pos_ += x_val_;
    y_pos_ += y_val_;
//    if(x_pos_<0)//check later
//    {
//        x_pos_ = 0;
//    }
//    else if(x_pos_ + width_frame_ > map_data.max_x_ )//check later
//    {
//        x_pos_ = map_data.max_x_ - width_frame_ - 1;
//    }
}
void EnemyObject::change_dir_move()
{
    int randVal = rand()%4 + 1;
    switch(randVal)
    {
    case 1:
        {
            input_type_.right_ = 1;
            input_type_.left_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
        }
        break;
    case 2:
        {
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
        }
        break;
    case 3:
        {
            input_type_.up_ = 1;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
        }
        break;
    case 4:
        {
            input_type_.down_ = 1;
            input_type_.up_ = 0;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
        }
        break;
    }
    return;
}
void EnemyObject::UpdateImage(SDL_Renderer* des)
{
    if(type_move_==STATIC_ENEMY) return;
    if(input_type_.left_==1)
    {
        LoadImg("img/enemy/enemy_left.png",des);
    }
    else if(input_type_.right_==1)
    {
        LoadImg("img/enemy/enemy_right.png",des);
    }
    else if(input_type_.up_==1)
    {
        LoadImg("img/enemy/enemy_up.png",des);
    }
    else if(input_type_.down_==1)
    {
        LoadImg("img/enemy/enemy_down.png",des);
    }
}
void EnemyObject::set_input_type_()
{
    int randVal = rand()%4 + 1;
    switch(randVal)
    {
    case 1:
        {
            input_type_.right_ = 1;
            input_type_.left_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
        }
        break;
    case 2:
        {
            input_type_.left_ = 1;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
            input_type_.up_ = 0;
        }
        break;
    case 3:
        {
            input_type_.up_ = 1;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
            input_type_.down_ = 0;
        }
        break;
    case 4:
        {
            input_type_.down_ = 1;
            input_type_.up_ = 0;
            input_type_.left_ = 0;
            input_type_.right_ = 0;
        }
        break;
    }
    return;
}
void EnemyObject::InitBullet(BulletObject* p_bullet, SDL_Renderer* screen)
{
    if(p_bullet!=NULL)
    {
        bool ret = p_bullet->LoadImg("img//bullet1.png",screen);
        p_bullet->set_is_move(true);
        p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
        p_bullet->SetRect(rect_.x + width_frame_*0.25, rect_.y + height_frame_);
        p_bullet->set_x_val(ENEMY_BULLET_SPEED);
        p_bullet->set_y_val(ENEMY_BULLET_SPEED);

        bullet_list_.push_back(p_bullet);
    }
}
void EnemyObject::MakeBullet(SDL_Renderer* screen,Map& map_data)
{
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
                p_bullet->set_is_move(true);
                p_bullet->SetRect(rect_.x + width_frame_*0.3, rect_.y + height_frame_*0.5);
            }
        }
    }
}
void EnemyObject::RemoveBullet(const int& index)
{
    int size = bullet_list_.size();
    if(size>0 && index<size)
    {
        BulletObject* p_bullet = bullet_list_[index];
        bullet_list_.erase(bullet_list_.begin() + index);
    }
}
