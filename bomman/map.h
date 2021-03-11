#ifndef MAP__H_
#define MAP__H_

#include "commonfunc.h"
#include "BaseObject.h"
using namespace std;

const int MAX_TILES = 5;


class TileMat : public BaseObject
{
public:
    TileMat(){;}
    ~TileMat(){;}

};


class GameMap
{
public:
    GameMap(){;}
    ~GameMap(){;}

    void LoadMap(char* name);
    void LoadTiles(SDL_Renderer* screen);
    void DrawMap(SDL_Renderer* screen);
private:
    Map game_map_;
    TileMat tile_mat[MAX_TILES];
};
#endif // MAP__H_
