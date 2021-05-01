
#include "Game.h"
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
bool PlayerCollision(PlayerObject &p_player,EnemyObject* p_enemy)
{
    return checkCollision(p_enemy->GetRectFrame(),p_player.GetRectFrame());
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
}
void PlayButtonHandle(LButton& Play,SDL_Event* e, bool& quit_menu, bool& is_playing)
{
    Play.handleEvent(e);
    if(Play.IsInside())
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            quit_menu = true;
            is_playing = false;
        }
    }

}
void HelpButtonHandle(LButton& Help, LButton& Back, SDL_Event* e, SDL_Renderer* des,
                      BaseObject& instrution, bool& quit_menu)
{
    Help.handleEvent(e);
    if(Help.IsInside())
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
            bool turn_back = false;
            while(!turn_back)
            {
               while(SDL_PollEvent(e)!=0)
                {
                    if(e->type == SDL_QUIT)
                    {
                        quit_menu = true;
                    }
                    BackButtonHandle(Back,e,turn_back);
                }
                instrution.Render(des,0);
                Back.render(des);
                SDL_RenderPresent(des);
            }
        }
    }
}
void BackButtonHandle(LButton& Back, SDL_Event* e, bool& turn_back)
{
    Back.handleEvent(e);
    if(Back.IsInside())
    {
        if(e->type == SDL_MOUSEBUTTONDOWN)
        {
           turn_back = true;
        }
    }
}
void ExitButtonHandle(LButton& Exit, SDL_Event* e, bool& quit_menu)
{
    Exit.handleEvent(e);
    if(Exit.IsInside()&&e->type==SDL_MOUSEBUTTONDOWN)
    {
        quit_menu = true;
    }
}
void scene(SDL_Renderer* gRenderer)
{
    BaseObject g_scene;
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img//bg1.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img//bg2.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    SDL_RenderClear(gRenderer);
    g_scene.LoadImg("img//bg3.png",gRenderer);
    g_scene.Render(gRenderer,NULL);
    SDL_RenderPresent(gRenderer);
    SDL_Delay(2000);
    g_scene.Free();
}
