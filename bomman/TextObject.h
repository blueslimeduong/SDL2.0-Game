#ifndef TEXTOBJECT__H_
#define TEXTOBJECT__H_

#include "commonfunc.h"
using namespace std;
class TextObject
{
public:
    TextObject();
    ~TextObject();
    enum TextColor
    {
        RED_TEXT = 0,
        WHITE_TEXT = 1,
        BLACK_TEXT = 2,
    };

    bool LoadFromFile(string path);
    bool LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen);
    void Free();
    void SetColor(Uint8 red, Uint8 green, Uint8 blue);
    void SetColor(int type);

    void RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip=NULL);
    int GetWidth() const {return width_;}
    int GetHeight() const {return height_;}

    void SetText(const string& text){str_val_=text;}
    string GetText(){return str_val_;}
private:
    string str_val_;
    SDL_Color text_color_;
    SDL_Texture* texture_;
    int width_;
    int height_;
};
#endif // TEXTOBJECT__H_
