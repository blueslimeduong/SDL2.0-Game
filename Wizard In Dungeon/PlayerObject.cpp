
#include "PlayerObject.h"

PlayerObject::PlayerObject()
{
    frame_ = 0;

    x_pos_= 64;
    y_pos_= 192;

    x_val_= 0;
    y_val_= 0;

    width_frame_=0;
    height_frame_=0;

    status_=-1;
    life_point_ = 3;

    input_type_.left_=0;
    input_type_.right_=0;
    input_type_.down_=0;
    input_type_.up_=0;

    maxBullet_ = 2;
    player_speed_ = 2.5;

    level_up = false;
}
PlayerObject::~PlayerObject()
{

}

bool PlayerObject::LoadImg(string path, SDL_Renderer* screen)
{
    bool ret = BaseObject::LoadImg(path,screen);
    if(ret==true)
    {
        width_frame_ = rect_.w/Frame;
        height_frame_ = rect_.h;
        for(int i=0; i<Frame; i++)
        {
            frame_clips_[i].x = i*width_frame_;
            frame_clips_[i].y = 0;
            frame_clips_[i].w = width_frame_;
            frame_clips_[i].h = height_frame_;
        }
    }
}
SDL_Rect PlayerObject::GetRectFrame()
{
    SDL_Rect rect;
    rect.x = rect_.x;
    rect.y = rect_.y;
    rect.h = height_frame_;
    rect.w = width_frame_;
    return rect;
}
void PlayerObject::Show(SDL_Renderer* des)
{
    UpdateImagePlayer(des);
    if(input_type_.left_==1||input_type_.right_==1||input_type_.up_==1||input_type_.down_==1)
    {
        frame_++;

    }
    else
    {
        frame_ = 0;
    }
    if(frame_>=Frame)
    {
        frame_=0;
    }
    rect_.x = x_pos_;
    rect_.y = y_pos_;

    SDL_Rect* current_clip = &frame_clips_[frame_];

    SDL_Rect renderQuad = {rect_.x,rect_.y,width_frame_,height_frame_};

    SDL_RenderCopy(des, p_object_,current_clip,&renderQuad);
}
void PlayerObject::HandleInputAction(SDL_Event events, SDL_Renderer* screen, Mix_Chunk* fire_sound)
{
    if(events.type == SDL_KEYDOWN)
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                status_ = WALK_RIGHT;
                input_type_.right_=1;
                input_type_.left_=0;
                input_type_.down_=0;
                input_type_.up_=0;
            }
            break;
        case SDLK_LEFT:
            {
                status_ = WALK_LEFT;
                input_type_.left_=1;
                input_type_.right_=0;
                input_type_.down_=0;
                input_type_.up_=0;
            }
            break;
        case SDLK_UP:
            {
                status_ = WALK_UP;
                input_type_.up_ = 1;
                input_type_.left_=0;
                input_type_.right_=0;
                input_type_.down_=0;
            }
            break;
        case SDLK_DOWN:
            {
                status_ = WALK_DOWN;
                input_type_.down_ = 1;
                input_type_.left_=0;
                input_type_.right_=0;
                input_type_.up_=0;
            }
            break;
        case SDLK_SPACE:
            {
                BulletObject* p_bullet = new BulletObject();
                p_bullet->LoadImg("img//bullet1.png",screen);

                switch(status_)
                {
                case WALK_LEFT:
                    {
                       p_bullet->set_bullet_dir(BulletObject::DIR_LEFT);
                       p_bullet->SetRect(this->rect_.x, rect_.y + height_frame_*0.5);
                    }
                   break;
                case WALK_RIGHT:
                    {
                        p_bullet->set_bullet_dir(BulletObject::DIR_RIGHT);
                        p_bullet->SetRect(this->rect_.x + width_frame_*0.5, rect_.y + height_frame_*0.5);
                    }
                    break;
                case WALK_UP:
                    {
                        p_bullet->set_bullet_dir(BulletObject::DIR_UP);
                        p_bullet->SetRect(this->rect_.x + width_frame_*0.25, rect_.y);
                    }
                    break;
                case WALK_DOWN:
                    {
                        p_bullet->set_bullet_dir(BulletObject::DIR_DOWN);
                        p_bullet->SetRect(this->rect_.x + width_frame_*0.25, rect_.y + height_frame_);
                    };
                    break;
                }

                p_bullet->set_x_val(BULLET_SPEED);
                p_bullet->set_y_val(BULLET_SPEED);
                p_bullet->set_is_move(true);
                if(p_bullet_list_.size()<maxBullet_)
                {
                    Mix_PlayChannel(-1,fire_sound,0);
                    p_bullet_list_.push_back(p_bullet);
                }
            }
        }
    }
    else if(events.type == SDL_KEYUP )
    {
        switch(events.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                input_type_.right_=0;

            }
            break;
        case SDLK_LEFT:
            {
                input_type_.left_=0;
            }
            break;
        case SDLK_UP:
            {
                input_type_.up_ = 0;
            }
            break;
        case SDLK_DOWN:
            {
                input_type_.down_ = 0;
            }
            break;
        default:
            break;
        }
    }
}
void PlayerObject::HandleBullet(SDL_Renderer* des, Map &map_data, Mix_Chunk* Crate)
{
    for(int i=0; i < p_bullet_list_.size(); i++)
    {
        BulletObject* p_bullet = p_bullet_list_[i];
        if(p_bullet != NULL)
        {
            if(p_bullet->get_is_move()==true)
            {
                p_bullet->HandleMove(map_data,Crate);
                p_bullet->Render(des);
            }
            else
            {
                p_bullet_list_.erase(p_bullet_list_.begin() + i);
                if(p_bullet != NULL)
                {
                    delete p_bullet;
                    p_bullet = NULL;
                }
            }
        }
    }
}
void PlayerObject::DoPlayer(Map& map_data, Mix_Chunk* Pick)
{
    x_val_ = 0;
    y_val_ = 0;

    if(input_type_.left_==1)
    {
        x_val_ -= player_speed_;
    }
    else if(input_type_.right_==1)
    {
        x_val_ += player_speed_;
    }
    else if(input_type_.up_==1)
    {
        y_val_ -= player_speed_;
    }
    else if(input_type_.down_==1)
    {
        y_val_ += player_speed_;
    }
    CheckToMap(map_data, Pick);
}

void PlayerObject:: CheckToMap(Map& map_data, Mix_Chunk* Pick)
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
            if(val1==SPEED_TILE||val2==SPEED_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                IncreaseSpeed();
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;

            }
            else if(val1==BULLET_TILE||val2==BULLET_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                IncreaseBullet();
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
            }
             else if(val1==LIFE_TILE||val2==LIFE_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                RefillLifePoint();
                map_data.tile[y1][x2] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1==25||val2==25)
            {
                level_up = true;
            }
            else if(val1!=BLANK_TILE || val2!=BLANK_TILE)
            {
                x_pos_ = x2*TILE_SIZE;
                x_pos_ -= width_frame_ + 1;
                x_val_ = 0;
            }
        }
        else if(x_val_ < 0)
        {
            int val1 = map_data.tile[y1][x1];
            int val2 = map_data.tile[y2][x1];
            if (val1==SPEED_TILE||val2==SPEED_TILE)
            {
                 Mix_PlayChannel(-1,Pick,0);
                 IncreaseSpeed();
                 map_data.tile[y1][x1] = 0;
                 map_data.tile[y2][x1] = 0;
            }
            else if (val1==BULLET_TILE||val2==BULLET_TILE)
            {
                 Mix_PlayChannel(-1,Pick,0);
                 IncreaseBullet();
                 map_data.tile[y1][x1] = 0;
                 map_data.tile[y2][x1] = 0;
            }
            else if (val1==LIFE_TILE||val2==LIFE_TILE)
            {
                 Mix_PlayChannel(-1,Pick,0);
                 RefillLifePoint();
                 map_data.tile[y1][x1] = 0;
                 map_data.tile[y2][x1] = 0;
            }
              else if(val1==ESCAPE_TILE||val2==ESCAPE_TILE)
            {
                level_up = true;
            }
            else if(val1!=BLANK_TILE ||val2!=BLANK_TILE)
            {
                x_pos_ = (x1+1)*TILE_SIZE;
                x_val_ = 0;
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
            if(val1==SPEED_TILE||val2==SPEED_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                IncreaseSpeed();
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1==BULLET_TILE||val2==BULLET_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                IncreaseBullet();
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1==LIFE_TILE||val2==LIFE_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                RefillLifePoint();
                map_data.tile[y2][x1] = 0;
                map_data.tile[y2][x2] = 0;
            }
            else if(val1==ESCAPE_TILE||val2==ESCAPE_TILE)
            {
                level_up = true;
            }
            else if(val1!=BLANK_TILE || val2!=BLANK_TILE)
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
            if(val1==SPEED_TILE||val2==SPEED_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                IncreaseSpeed();
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
            else if(val1==BULLET_TILE||val2==BULLET_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                IncreaseBullet();
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
            else if(val1==LIFE_TILE||val2==LIFE_TILE)
            {
                Mix_PlayChannel(-1,Pick,0);
                RefillLifePoint();
                map_data.tile[y1][x1] = 0;
                map_data.tile[y1][x2] = 0;
            }
            else if(val1==ESCAPE_TILE||val2==ESCAPE_TILE)
            {
                level_up = true;
            }
            else if(val1!=BLANK_TILE || val2!=BLANK_TILE)
             {
                 y_pos_ =  (y1 + 1)*TILE_SIZE;
                 y_val_ = 0;
             }
        }
    }
    x_pos_ += x_val_;
    y_pos_ += y_val_;

}
void PlayerObject::UpdateImagePlayer(SDL_Renderer* des)
{
    switch(status_)
    {
    case WALK_LEFT:
       LoadImg("img/player/player_left2.png",des);
       break;
    case WALK_RIGHT:
        LoadImg("img/player/player_right2.png",des);
        break;
    case WALK_UP:
        LoadImg("img/player/player_up2.png",des);
        break;
    case WALK_DOWN:
        LoadImg("img/player/player_down2.png",des);
        break;
    }

}
void PlayerObject::RemoveBullet(const int& index)
{
    int size = p_bullet_list_.size();
    if(size>0 && index<size)
    {
        BulletObject* p_bullet = p_bullet_list_[index];
        p_bullet_list_.erase(p_bullet_list_.begin() + index);
    }
}

void PlayerObject::IncreaseBullet()
{
    maxBullet_ += 1;
    if(maxBullet_ >= PLAYER_MAX_BULLET)
    {
        maxBullet_ = PLAYER_MAX_BULLET;
    }
    return;
}
void PlayerObject::IncreaseSpeed()
{
    player_speed_ += 0.5;
    if(player_speed_ >= PLAYER_MAX_SPEED)
    {
        player_speed_ = PLAYER_MAX_SPEED;
    }
    return;
}
void PlayerObject::RefillLifePoint()
{
    life_point_ += 1;
    if(life_point_>=MAX_LIFE_POINT)
    {
        life_point_ = MAX_LIFE_POINT;
    }
    return;
}
void PlayerObject::respawn(Mix_Chunk* Die)
{
    Mix_PauseMusic();
    Mix_PlayChannel(-1,Die,0);
    life_point_--;
    SDL_Delay(2500);
    SetRect(0,0);
    x_pos_ = SPAWN_X;
    y_pos_ = SPAWN_Y;
    x_val_ = 0;
    y_val_ = 0;
    status_ = WALK_DOWN;
    Mix_ResumeMusic();
    return;
}
void PlayerObject::next_level()
{
    Mix_PauseMusic();
    SetRect(0,0);
    x_pos_ = SPAWN_X;
    y_pos_ = SPAWN_Y;
    x_val_ = 0;
    y_val_ = 0;
    status_ = WALK_DOWN;
    Mix_ResumeMusic();
    return;
}
