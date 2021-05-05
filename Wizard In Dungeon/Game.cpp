
#include "Game.h"

bool checkCollision(const SDL_Rect &a,const SDL_Rect &b )
{
    // The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;  //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;

}

void EnemyCollision(PlayerObject &p_player, vector<EnemyObject*> &enemies_list,unsigned int &score_val, Mix_Chunk* gExplosion)
{
    vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
    for(int i=0; i<bullet_arr.size(); i++)
        {
            BulletObject* p_bullet = bullet_arr[i];
            if(p_bullet!=NULL)
            {

                for(int j=0; j<enemies_list.size(); j++)
                {
                    EnemyObject* p_enemy = enemies_list[j];
                    if(p_enemy!=NULL)
                    {
                        SDL_Rect jRect = p_enemy->GetRectFrame();
                        SDL_Rect iRect = p_bullet->GetRect();
                        bool isCol = checkCollision(jRect,iRect);
                        if(isCol)
                        {
                            score_val += 10;
                            Mix_PlayChannel(-1,gExplosion,0);
                            p_player.RemoveBullet(i);
                            p_enemy->Free();
                            enemies_list.erase(enemies_list.begin() + j);
                        }
                    }
                }
            }
        }
}
void BossCollision(PlayerObject &p_player, BossObject &p_boss, Mix_Chunk* gExplosion)
{
    vector<BulletObject*> bullet_arr = p_player.get_bullet_list();
    for(int i=0; i<bullet_arr.size(); i++)
    {
        BulletObject* p_bullet = bullet_arr[i];
        if(p_bullet!=NULL)
        {
            bool isCol = checkCollision(p_bullet->GetRect(),p_boss.GetRectFrame());
            if(isCol)
            {
                Mix_PlayChannel(-1,gExplosion,0);
                p_player.RemoveBullet(i);
                p_boss.beAttacked();
            }
        }
    }
}
bool PlayerCollision(PlayerObject &p_player,EnemyObject* p_enemy)
{

    SDL_Rect rect_player = p_player.GetRectFrame();
    vector<BulletObject*> EBullet_list = p_enemy->get_bullet_list();
    for(int j=0; j<EBullet_list.size(); j++)
    {
        BulletObject* p_Ebullet = EBullet_list[j];
        if(p_Ebullet!=NULL)
        {
            bool isCol1 = checkCollision(p_Ebullet->GetRect(),rect_player);
            if(isCol1)
            {
                //p_enemy->RemoveBullet(j);
                p_Ebullet->set_is_move(false);

                return true;
            }
        }
    }
    return checkCollision(p_enemy->GetRectFrame(),p_player.GetRectFrame());
}

bool PlayerCollisionBoss(PlayerObject &p_player,BossObject* p_boss)
{

    SDL_Rect rect_player = p_player.GetRectFrame();
    vector<BulletObject*> BBullet_list = p_boss->get_bullet_list();
    for(int j=0; j<BBullet_list.size(); j++)
    {
        BulletObject* p_Bbullet = BBullet_list[j];
        if(p_Bbullet!=NULL)
        {
            bool isCol = checkCollision(p_Bbullet->GetRect(),rect_player);
            if(isCol)
            {

                p_boss->RemoveBullet(j);
//                p_Bbullet->set_is_move(false);

                return true;
            }
        }
    }
    return checkCollision(p_boss->GetRectFrame(),p_player.GetRectFrame());
}
void PlayButtonHandle(LButton& Play,SDL_Event* e, Mix_Chunk* Click ,bool& quit_menu, bool& is_playing)
{
    Play.handleEvent(e);
    if(Play.IsInside())
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(-1,Click,0);
            quit_menu = true;
            is_playing = false;
        }
    }

}
void HelpButtonHandle(LButton& Help, LButton& Back, SDL_Event* e, SDL_Renderer* des,
                      BaseObject& instrution,Mix_Chunk* Click , bool& quit_menu)
{
    Help.handleEvent(e);
    if(Help.IsInside())
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(-1,Click,0);
            bool turn_back = false;
            while(!turn_back)
            {
               while(SDL_PollEvent(e)!=0)
                {
                    if(e->type == SDL_QUIT)
                    {
                        turn_back = true;
                    }
                    BackButtonHandle(Back,e,Click,turn_back);
                }
                instrution.Render(des,0);
                Back.render(des);
                SDL_RenderPresent(des);
            }
        }
    }
}
void BackButtonHandle(LButton& Back, SDL_Event* e, Mix_Chunk* Click ,bool& turn_back)
{
    Back.handleEvent(e);
    if(Back.IsInside())
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            Mix_PlayChannel(-1,Click,0);
            turn_back = true;
        }
    }
}
void ExitButtonHandle(LButton& Exit, SDL_Event* e, Mix_Chunk* Click , bool& quit_menu)
{
    Exit.handleEvent(e);
    if(Exit.IsInside()&&e->type==SDL_MOUSEBUTTONDOWN)
    {
        Mix_PlayChannel(-1,Click,0);
        quit_menu = true;
    }
}
void ContinueButtonHandle(LButton& Continue,SDL_Event* e,Mix_Chunk* Click , bool& isPaused)
{
    Continue.handleEvent(e);
    if(Continue.IsInside()&&e->type==SDL_MOUSEBUTTONDOWN)
    {
        Mix_PlayChannel(-1,Click,0);
        Mix_ResumeMusic();
        isPaused = true;
    }
}
void EscButton(LButton& Continue, LButton& Back, SDL_Event* e, SDL_Renderer* des,Mix_Chunk* Click , bool& is_quit)
{
    bool turn_back = false;
    Mix_PauseMusic();
    while(!turn_back)
    {
       while(SDL_PollEvent(e)!=0)
        {
            if(e->type == SDL_QUIT)
            {
                is_quit = true;
            }
            ContinueButtonHandle(Continue,e,Click,turn_back);
            BackButtonHandle(Back,e,Click,is_quit);
            if(is_quit) turn_back = true;
        }
        Continue.render(des);
        Back.render(des);
        SDL_RenderPresent(des);
    }
}
void BadEnding1(SDL_Renderer* gRenderer)
{
    BaseObject g_scene;
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/bad12.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/bad13.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/bad14.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/bad15.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/bad16.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/lose1.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    g_scene.Free();
}
void BadEnding2(SDL_Renderer* gRenderer)
{
    BaseObject g_scene;
    for(int i=0; i<2; i++)
    {
        SDL_RenderClear(gRenderer);
        g_scene.LoadImg("img/scene/bad21.png",gRenderer);
        g_scene.Render(gRenderer,NULL);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(500);
        SDL_RenderClear(gRenderer);
        g_scene.LoadImg("img/scene/bad22.png",gRenderer);
        g_scene.Render(gRenderer,NULL);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(500);
    }
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/lose1.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    g_scene.Free();
}
void GoodEnding(SDL_Renderer* gRenderer)
{
    BaseObject g_scene;
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/good1.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/good2.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/good3.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/good4.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(500);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/win.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    g_scene.Free();
}
void NextLevelScene(SDL_Renderer* gRenderer)
{
    BaseObject g_scene;
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/next1.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(1000);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/next2.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(1000);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img/scene/next3.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(1000);

    g_scene.Free();
}
void DeleteEnemyList(vector<EnemyObject*> &enemies_list)
{
    for(int i=0; i< enemies_list.size(); i++)
                {
                    EnemyObject* p_enemy = enemies_list[i];
                    if(p_enemy!=NULL)
                    {
                        p_enemy->Free();
                        p_enemy = NULL;
                    }
                }
    enemies_list.clear();
}
