#ifndef COMMONFUNC__H_
#define COMMONFUNC__H_

#include <windows.h>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

static SDL_Window* g_window = NULL;
static SDL_Renderer* g_screen = NULL;
static SDL_Event g_event;


//Screen
const int FRAME_PER_SECOND = 30; //FPS
const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 640;
const int SCREEN_BPP = 32;

const int COLOR_KEY_R = 58;
const int COLOR_KEY_G = 29;
const int COLOR_KEY_B = 58;

const int RENDER_DRAW_COLOR = 0xff; // =255

#define TILE_SIZE 32

#define BLANK_TILE 0
const int BREAKABLE_TILE = 16;
const int LIFE_TILE = 21;
const int SPEED_TILE = 22;
const int BULLET_TILE = 23;

#define MAX_MAP_X 30
#define MAX_MAP_Y 20

struct Map
{
    int start_x_;
    int start_y_;

    int max_x_;
    int max_y_;

    int tile[MAX_MAP_Y][MAX_MAP_X];
    char* file_name;
};

struct Input
{
    int left_;
    int right_;
    int up_;
    int down_;
};
#endif // COMMONFUNC__H_
