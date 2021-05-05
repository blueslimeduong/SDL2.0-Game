#ifndef BUTTON__H_
#define BUTTON__H_
#include "commonfunc.h"
#include "BaseObject.h"
enum LButtonSprite
{
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_TOTAL = 2
};
class LButton : public BaseObject
{
public:
    //Initializes internal variables
    LButton();

    LButton(int x, int y);
    //Sets top left position
    void setPosition( int x, int y );

    //Handles mouse event
    bool IsInside(){return inside;}
    void handleEvent(SDL_Event* e);
    bool LoadImg(string path, SDL_Renderer* screen);

    //Shows button sprite
    void render(SDL_Renderer* des);

private:
    //Top left position
    SDL_Point mPosition;
    bool inside;
    SDL_Rect clips[BUTTON_TOTAL];
    //Currently used global sprite
    LButtonSprite mCurrentSprite;
};
#endif // BUTTON__H_
