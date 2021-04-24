#include <iostream>
#include <ctime>
#include "commonfunc.h"
#include "BaseObject.h"
#include "map.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "EnemyObject.h"
using namespace std;
int dem = 0;
BaseObject g_background;
bool InitData()
{
    bool success = true;
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0)
    {
        return false;
    }
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    g_window = SDL_CreateWindow("Wizard In Dungeon",
                                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if(g_window == NULL)
    {
        success = false;
    }
    else
    {
        g_screen = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
        if(g_screen == NULL)
        {
            success = false;
        }
        else
        {
            SDL_SetRenderDrawColor(g_screen, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR, RENDER_DRAW_COLOR);
            int imgFlags = IMG_INIT_PNG;
            if(!(IMG_Init(imgFlags)&&imgFlags))
            {
                success = false;
            }
        }

    }
    return success;
}
bool LoadBackGround()
{
    bool ret = g_background.LoadImg("img//bg.png", g_screen);
    if(ret == false)
    {
        return false;
    }
    return true;
}
void close()
{
    g_background.Free();

    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    IMG_Quit();
    SDL_Quit();
    return;
}
vector<EnemyObject*>MakeEnemyList()
{
    vector<EnemyObject*> list_enemies;

    EnemyObject* enemies_objs = new EnemyObject[4];
    for(int i=0; i<4; i++)
    {
        EnemyObject* p_enemy  = enemies_objs + i;
        if(p_enemy!=NULL)
        {
            p_enemy->LoadImg("img/enemy11.png",g_screen);
            p_enemy->set_clips();
            p_enemy->set_type_move(EnemyObject::STATIC_ENEMY);
            p_enemy->set_x_pos(416 + i*128);
            p_enemy->set_y_pos(320);
            BulletObject* p_bullet = new BulletObject();
            p_enemy->InitBullet(p_bullet,g_screen);
            list_enemies.push_back(p_enemy);
        }
    }

    int M_E_Num = 0;
    EnemyObject* moving_enemies = new EnemyObject[15];
    for(int i=0; i<5; i++){
    for(int j=0; j<3; j++)
    {
        EnemyObject* p_enemy = moving_enemies+ M_E_Num;
        M_E_Num++;
        if(p_enemy!=NULL)
        {
            p_enemy->LoadImg("img/player_down.png",g_screen);
            p_enemy->set_clips();
            p_enemy->set_type_move(EnemyObject::MOVING_ENEMY);
//            p_enemy->set_input_type_();
            p_enemy->set_x_pos(224 + i*128);
            p_enemy->set_y_pos(224 + j*160);

            list_enemies.push_back(p_enemy);
        }
    }
    }
    return list_enemies;
}

int main(int argc, char* argv[])
{
    ImpTimer fps_timer;
    srand(time(0));

    if(InitData()==false)
    {
        cout << "INITDATA False" << endl;
        return -1;
    }

    if(LoadBackGround()==false)
    {
        cout << "LoadBackGround False" << endl;
        return -1;
    }

    GameMap game_map;
    game_map.LoadMap("map//map.txt");
    game_map.LoadTiles(g_screen);

    PlayerObject p_player;
    p_player.LoadImg("img//player_down2.png",g_screen);
    p_player.set_clips();

    vector<EnemyObject*> enemies_list = MakeEnemyList();

    bool is_quit = false;
    while(!is_quit)
    {
        fps_timer.start();
        while(SDL_PollEvent(&g_event)!=0)
        {
            if(g_event.type == SDL_QUIT)
            {
                is_quit = true;
            }
            p_player.HandleInputAction(g_event,g_screen);
        }

        SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
        SDL_RenderClear(g_screen);

        g_background.Render(g_screen, NULL);
        game_map.DrawMap(g_screen);

        Map map_data = game_map.getMap();

        p_player.HandleBullet(g_screen,map_data);
        p_player.DoPlayer(map_data);
        p_player.Show(g_screen);

        game_map.UpdateMap(map_data);

        for(int i=0; i<enemies_list.size(); i++)
        {
            EnemyObject* p_enemy = enemies_list[i];
            if(p_enemy!=NULL)
            {
//                p_enemy->SetMapXY(map_data.start_x_,map_data.start_y_);
                p_enemy->DoEnemy(map_data);
                p_enemy->MakeBullet(g_screen,map_data);
                p_enemy->Show(g_screen);

                //Check Collision giua enemy va bullet enemy voi player
                bool isCol1 = false, isCol2= false;
                SDL_Rect rect_player = p_player.GetRectFrame();

                vector<BulletObject*> EBullet_list = p_enemy->get_bullet_list();
                for(int j=0; j<EBullet_list.size(); j++)
                {
                    BulletObject* p_Ebullet = EBullet_list[j];
                    if(p_Ebullet!=NULL)
                    {
                        isCol1 = checkCollision(p_Ebullet->GetRect(),rect_player);
                        if(isCol1)
                        {
                            p_enemy->RemoveBullet(j);
                            break;
                        }
                    }
                }

                SDL_Rect rect_enemy = p_enemy->GetRectFrame();
                isCol2 = checkCollision(rect_enemy,rect_player);

                if(isCol1||isCol2)
                {
//                    if(MessageBox(NULL,L,MB_OK | MB_ICONSTOP)==IDOK)
//                    {
//                        p_enemy->Free();
//                        close();
//                        SDL_Quit();
//                        return;
//                    }
                    cout << "DIE" << dem++ <<endl;
                }
            }
        }
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
                            p_player.RemoveBullet(i);
                            p_enemy->Free();
                            enemies_list.erase(enemies_list.begin() + j);
                        }
                    }
                }
            }
        }

        SDL_RenderPresent(g_screen);

        int real_imp_time = fps_timer.get_ticks();
        int time_per_frame = 1000/FRAME_PER_SECOND; // mili sec

        if(real_imp_time<time_per_frame)
        {
            int delay_time = time_per_frame - real_imp_time;
            SDL_Delay(delay_time);
        }
    }

    //giai phong bo nho
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
    close();
    return 0;
}
