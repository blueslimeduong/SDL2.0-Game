#include "TextObject.h"

TextObject::TextObject()
{
    text_color_.r = 255;
    text_color_.g = 255;
    text_color_.b = 255;
    texture_ = NULL;
}
TextObject::~TextObject()
{

}

bool TextObject::LoadFromRenderText(TTF_Font* font,SDL_Renderer* screen)
{
    SDL_Surface* text_texture = TTF_RenderText_Solid(font,str_val_.c_str(),text_color_);
    if(text_texture)
    {
        texture_ = SDL_CreateTextureFromSurface(screen,text_texture);
        width_ = text_texture->w;
        height_ = text_texture->h;

        SDL_FreeSurface(text_texture);
    }
    return texture_!=NULL;
}
void TextObject::Free()
{
    if(texture_!=NULL)
    {
        SDL_DestroyTexture(texture_);
        texture_ = NULL;
    }
}
void TextObject::SetColor(Uint8 red, Uint8 green, Uint8 blue)
{
    text_color_.r = red;
    text_color_.g = green;
    text_color_.b = blue;
}
void TextObject::SetColor(int type)
{
    switch(type)
    {
    case RED_TEXT:
        text_color_.r = 255;
        text_color_.g = 0;
        text_color_.b = 0;
        break;
    case WHITE_TEXT:
        text_color_.r = 255;
        text_color_.g = 255;
        text_color_.b = 255;
        break;
    case BLACK_TEXT:
        text_color_.r = 0;
        text_color_.g = 0;
        text_color_.b = 0;
        break;

    }
}
void TextObject::RenderText(SDL_Renderer* screen, int x, int y, SDL_Rect* clip)
{
    SDL_Rect renderQuad = {x, y, width_, height_};
    if(clip!=NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopy(screen,texture_,clip, &renderQuad);
}
