#include <iostream>
#include <ctime>
#include "commonfunc.h"
#include "BaseObject.h"
#include "map.h"
#include "PlayerObject.h"
#include "ImpTimer.h"
#include "EnemyObject.h"
#include "BossObject.h"
#include "TextObject.h"
#include "Game.h"
//
using namespace std;

TTF_Font* font_time = NULL;
Mix_Chunk* gFireball = NULL;
Mix_Chunk* gExplosion = NULL;
Mix_Chunk* gClick = NULL;
Mix_Chunk* gCrate = NULL;
Mix_Chunk* gPickup = NULL;
Mix_Chunk* gDie = NULL;
Mix_Chunk* gGameOver = NULL;
Mix_Chunk* gGameClear = NULL;
Mix_Music* gMenuMusic = NULL;
Mix_Music* gIngameMusic = NULL;

BaseObject g_background;
BaseObject g_menugame;
BaseObject g_instruction;
TextObject score_game;
TextObject time_game;
TextObject life_point_game;
TextObject boss_LP;
LButton PlayButton(BUTTON_X,PLAY_BUTTON_Y);
LButton HelpButton(BUTTON_X,HELP_BUTTON_Y);
LButton ExitButton(BUTTON_X,EXIT_BUTTON_Y);
LButton BackButton(BUTTON_X,BACK_BUTTON_Y);
LButton ContinueButton(BUTTON_X,CONTINUE_BUTTON_Y);

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

        if(TTF_Init() == -1)
        {
            success = false;
        }
        else
        {
            font_time = TTF_OpenFont("font/Aller_Bd.ttf", 20);
            if(font_time==NULL)
            {
                success = false;
            }
        }

        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        else
        {
            gFireball = Mix_LoadWAV("sound/Fireball+3.wav");
            gExplosion = Mix_LoadWAV("sound/Explosion+1.wav");
            gClick = Mix_LoadWAV("sound/button.wav");
            gCrate = Mix_LoadWAV("sound/crate.wav");
            gPickup = Mix_LoadWAV("sound/pickup.wav");
            gDie = Mix_LoadWAV("sound/die.wav");
            gGameClear = Mix_LoadWAV("sound/gameclear.wav");
            gGameOver = Mix_LoadWAV("sound/gameover.wav");
            gMenuMusic = Mix_LoadMUS("sound/Unravel.mp3");
            gIngameMusic = Mix_LoadMUS("sound/battle.mp3");
            if(gFireball==NULL||gExplosion==NULL||gClick==NULL||gPickup==NULL||gDie==NULL||
               gGameClear==NULL||gGameOver==NULL||gMenuMusic==NULL||gIngameMusic==NULL||gCrate==NULL)
            {
                success = false;
            }
        }

    }
    return success;
}
bool LoadPic()
{
    bool ret = g_background.LoadImg("img//bg2.png", g_screen);
    bool ret2 = g_menugame.LoadImg("img/menu//menu.png",g_screen);
    bool ret3 = g_instruction.LoadImg("img/menu/instruction.png", g_screen);
    if(ret == false||ret2 == false||ret3 == false)
    {
        cout << "Load Background failed." << endl;
        return false;
    }
    if(!PlayButton.LoadImg("img/menu/play_button.png",g_screen))
    {
        return false;
    }
    if(!HelpButton.LoadImg("img/menu/help_button.png",g_screen))
    {
        return false;
    }
    if(!ExitButton.LoadImg("img/menu/exit_button.png",g_screen))
    {
        return false;
    }
    if(!BackButton.LoadImg("img/menu/back_button.png",g_screen))
    {
        return false;
    }
    if(!ContinueButton.LoadImg("img/menu/continue_button.png",g_screen))
    {
        return false;
    }
    return true;
}
void close()
{
    g_background.Free();
    g_menugame.Free();
    g_instruction.Free();

    TTF_CloseFont(font_time);
    font_time = NULL;

    Mix_FreeChunk(gFireball);
    gFireball = NULL;
    Mix_FreeChunk(gExplosion);
    gExplosion = NULL;
    Mix_FreeChunk(gClick);
    gClick = NULL;
    Mix_FreeChunk(gCrate);
    gCrate = NULL;
    Mix_FreeMusic(gMenuMusic);
    gMenuMusic = NULL;
    Mix_FreeMusic(gIngameMusic);
    gIngameMusic = NULL;
    SDL_DestroyRenderer(g_screen);
    g_screen = NULL;

    SDL_DestroyWindow(g_window);
    g_window = NULL;

    TTF_Quit();
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
    return;
}
vector<EnemyObject*>MakeEnemyList()
{
    int StaticEnemy = 6;
    int MovingEnemy = 15;
    vector<EnemyObject*> list_enemies;

    EnemyObject* enemies_objs = new EnemyObject[StaticEnemy];
    for(int i=0; i<StaticEnemy; i++)
    {
        EnemyObject* p_enemy  = enemies_objs + i;
        if(p_enemy!=NULL)
        {
            p_enemy->LoadImg("img/enemy/static_enemy.png",g_screen);
            p_enemy->set_type_move(EnemyObject::STATIC_ENEMY);
            p_enemy->set_x_pos(160 + i*128);
            p_enemy->set_y_pos(320);
            BulletObject* p_bullet = new BulletObject();
            p_enemy->InitBullet(p_bullet,g_screen);
            list_enemies.push_back(p_enemy);
        }
    }

    int M_E_Num = 0;
    EnemyObject* moving_enemies = new EnemyObject[MovingEnemy];
    for(int i=0; i<5; i++)
    {
        for(int j=0; j<3; j++)
        {
            EnemyObject* p_enemy = moving_enemies+ M_E_Num;
            M_E_Num++;
            if(p_enemy!=NULL)
            {
                p_enemy->LoadImg("img/enemy/enemy_down.png",g_screen);
                p_enemy->set_type_move(EnemyObject::MOVING_ENEMY);
                p_enemy->set_input_type_();
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
    srand(time(0));
    ImpTimer TimeGame;
    ImpTimer fps_timer;
    if(InitData()==false)
    {
        cout << "INITDATA False" << endl;
        return -1;
    }
    if(LoadPic()==false)
    {
        cout << "LoadBackGround False" << endl;
        return -1;
    }

    // Text
    life_point_game.SetColor(TextObject::WHITE_TEXT);
    boss_LP.SetColor(TextObject::WHITE_TEXT);
    time_game.SetColor(TextObject::WHITE_TEXT);
    score_game.SetColor(TextObject::WHITE_TEXT);
    unsigned int score_val = 0;

    bool quit_game = false;
    bool quit_menu = false;
    bool is_quit = true;
    bool boss_level = false;
    bool is_win = false;
    while(!quit_game){
        Mix_PlayMusic(gMenuMusic,-1);
        TimeGame.start();
        //Menu
        while(!quit_menu)
        {
            TimeGame.paused();
            while(SDL_PollEvent(&g_event)!=0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    quit_game = true;
                }
                PlayButtonHandle(PlayButton,&g_event,gClick,quit_menu,is_quit);
                HelpButtonHandle(HelpButton,BackButton,&g_event,g_screen,g_instruction,gClick,quit_menu);
                ExitButtonHandle(ExitButton,&g_event,gClick,quit_game);
                if(quit_game)
                {
                    quit_menu = true;
                }
            }
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);
            g_menugame.Render(g_screen,0);

            PlayButton.render(g_screen);
            HelpButton.render(g_screen);
            ExitButton.render(g_screen);

            SDL_RenderPresent(g_screen);
        }
        GameMap game_map;
        game_map.LoadMap("map//map.txt");
        game_map.LoadTiles(g_screen);

        PlayerObject p_player;
        p_player.LoadImg("img/player/player_down2.png",g_screen);
//
        vector<EnemyObject*> enemies_list = MakeEnemyList();

        BossObject bossObject;
        bossObject.LoadImg("img/enemy/boss1.png",g_screen);
        bossObject.set_x_pos(300);
        bossObject.set_y_pos(200);

        Mix_PlayMusic(gIngameMusic,-1);
        Mix_VolumeMusic(90);
        TimeGame.unpaused();
        while(!is_quit)
        {
            fps_timer.start();
            while(SDL_PollEvent(&g_event)!=0)
            {
                if(g_event.type == SDL_QUIT)
                {
                    is_quit = true;
                }
                if(g_event.type == SDL_KEYDOWN)
                {
                    if(g_event.key.keysym.sym==SDLK_ESCAPE)
                    {
                        TimeGame.paused();
                        EscButton(ContinueButton,BackButton,&g_event,g_screen,gClick,is_quit);
                    }
                }
                p_player.HandleInputAction(g_event,g_screen,gFireball);
            }
            TimeGame.unpaused();
            SDL_SetRenderDrawColor(g_screen,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR,RENDER_DRAW_COLOR);
            SDL_RenderClear(g_screen);

            g_background.Render(g_screen, NULL);
            game_map.DrawMap(g_screen);

            Map map_data = game_map.getMap();

            p_player.HandleBullet(g_screen,map_data,gCrate);
            p_player.DoPlayer(map_data,gPickup);
            p_player.Show(g_screen);

            game_map.UpdateMap(map_data);

            for(int i=0; i<enemies_list.size(); i++)
            {
                EnemyObject* p_enemy = enemies_list[i];
                if(p_enemy!=NULL)
                {
                    p_enemy->DoEnemy(map_data);
                    p_enemy->MakeBullet(g_screen,map_data);
                    p_enemy->Show(g_screen);

                    //Check Collision giua enemy va bullet enemy voi player
                    if(PlayerCollision(p_player,p_enemy))
                    {
                        p_player.die();
                        p_player.respawn(gDie);
                    }
                }
            }
            EnemyCollision(p_player,enemies_list,score_val,gExplosion);
            // Show Text
            string str_time = "Time: ";
            Uint32 time_val = TimeGame.get_ticks()/1000;
            Uint32 val_time = 300 - time_val;
            if(val_time<=0)
            {
                DeleteEnemyList(enemies_list);
                Mix_PauseMusic();
                Mix_PlayChannel(-1,gGameOver,0);
                if(!boss_level)
                {
                    BadEnding1(g_screen);
                }
                else
                {
                    BadEnding2(g_screen);
                }
                is_quit = true;
            }
            else
            {
                string str_val = to_string(val_time);
                str_time += str_val;
                time_game.SetText(str_time);
                time_game.LoadFromRenderText(font_time,g_screen);
                time_game.RenderText(g_screen,SCREEN_WIDTH - 150,20);
            }

            string val_str_score = to_string(score_val);
            string strScore = "Score: " + val_str_score;
            score_game.SetText(strScore);
            score_game.LoadFromRenderText(font_time,g_screen);
            score_game.RenderText(g_screen,SCREEN_WIDTH - 500, 20);

            string lp_str_val = to_string(p_player.get_life_point());
            string strLP = "x" + lp_str_val;
            life_point_game.SetText(strLP);
            life_point_game.LoadFromRenderText(font_time,g_screen);
            life_point_game.RenderText(g_screen,130,20);

            // Boss xuat hien
            if(boss_level)
            {
                bossObject.DoEnemy(map_data);
                bossObject.MakeBullet(g_screen,map_data);
                bossObject.Show(g_screen);
                if(PlayerCollisionBoss(p_player,&bossObject))
                {
                    p_player.die();
                    p_player.respawn(gDie);
                }
                BossCollision(p_player,bossObject,gExplosion);
                string boss_lp_str = to_string(bossObject.get_boss_HP());
                string strBossHP = "Boss HP : " + boss_lp_str + " / 50";
                boss_LP.SetText(strBossHP);
                boss_LP.LoadFromRenderText(font_time,g_screen);
                boss_LP.RenderText(g_screen,SCREEN_WIDTH - 540,60);
            }

            SDL_RenderPresent(g_screen);

            // Chinh FPS
            int real_imp_time = fps_timer.get_ticks();
            int time_per_frame = 1000/FRAME_PER_SECOND; // mili sec

            if(real_imp_time<time_per_frame)
            {
                int delay_time = time_per_frame - real_imp_time;
                SDL_Delay(delay_time);
            }

          // Clear first map
            if(p_player.is_levelup())
            {
                p_player.set_level_up(false);
                DeleteEnemyList(enemies_list);
                p_player.respawn();
                TimeGame.start();
                game_map.LoadMap("map//map2.txt");
                game_map.LoadTiles(g_screen);
                boss_level = true;

            }
            if(boss_level && bossObject.get_boss_HP()<=0)
            {
                is_quit = true;
                Mix_PauseMusic();
                Mix_PlayChannel(-1,gGameClear,0);
            }
            if(p_player.get_life_point()<=0)
            {

                Mix_PauseMusic();
                Mix_PlayChannel(-1,gGameOver,0);
                if(!boss_level)
                {
                    DeleteEnemyList(enemies_list);
                    BadEnding1(g_screen);
                }
                else
                {
                    BadEnding2(g_screen);
                }
                is_quit = true;
            }
            if(is_quit)
            {
                quit_menu = false;
            }
        }
    }
    close();
    return 0;
}

