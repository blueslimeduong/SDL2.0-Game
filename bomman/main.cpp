#include <iostream>
#include "commonfunc.h"
#include "BaseObject.h"
#include "map.h"
#include "PlayerObject.h"
using namespace std;
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

    g_window = SDL_CreateWindow("Bomman",
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
    bool ret = g_background.LoadImg("img//background.png", g_screen);
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
int main(int argc, char* argv[])
{
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
    p_player.LoadImg("img//player_down.png",g_screen);
    p_player.set_clips();


    bool is_quit = false;
    while(!is_quit)
    {
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

        p_player.Show(g_screen);

        SDL_RenderPresent(g_screen);
    }

    close();
    return 0;
}