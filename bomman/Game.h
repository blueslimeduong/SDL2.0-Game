#ifndef GAME__H_
#define GAME__H_
#include "commonfunc.h"
#include "EnemyObject.h"
#include "PlayerObject.h"
#include "BulletObject.h"
#include "Button.h"

void EnemyCollision(PlayerObject &p_player, vector<EnemyObject*> &enemies_list,unsigned int &score_val, Mix_Chunk* gExplosion);
bool PlayerCollision(PlayerObject &p_player,EnemyObject* p_enemy);
vector<EnemyObject*>MakeEnemyList();
void scene(SDL_Renderer* gRenderer);
void PlayButtonHandle(LButton& Play,SDL_Event* e,Mix_Chunk* Click, bool& quit_menu, bool& is_playing);
void HelpButtonHandle(LButton& Help, LButton& Back, SDL_Event* e,SDL_Renderer* des,
                      BaseObject& instrution, Mix_Chunk* Click ,bool& quit_menu);
void BackButtonHandle(LButton& Back, SDL_Event* e,Mix_Chunk* Click ,bool& turn_back);
void ExitButtonHandle(LButton& Exit, SDL_Event* e,Mix_Chunk* Click, bool& quit_menu);
void EscButton(LButton& Continue, LButton& Back, SDL_Event* e, SDL_Renderer* des, Mix_Chunk* Click , bool& is_quit);
void ContinueButtonHandle(LButton& Continue,SDL_Event* e, Mix_Chunk* Click ,bool& isPaused);
#endif // GAME__H
