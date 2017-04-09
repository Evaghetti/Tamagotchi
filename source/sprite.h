#ifndef SPRITE_H_INCLUDED
#define SPRITE_H_INCLUDED
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

typedef struct{
    ALLEGRO_BITMAP* Spritesheet;
    int larguraSpr, alturaSpr;
    int posFolX, posFolY;
}Sprite;

Sprite iniSpr(int larguraSpr, int alturaSpr, const char cam[], const int posFolX, const int posFolY){
    Sprite temp;
    temp.Spritesheet = al_load_bitmap(cam);
    temp.posFolX = posFolX;
    temp.posFolY = posFolY;
    temp.alturaSpr = alturaSpr;
    temp.larguraSpr = larguraSpr;
    al_convert_mask_to_alpha(temp.Spritesheet,al_map_rgb(0,255,0));
    return temp;
}

ALLEGRO_BITMAP* pegarSprite(Sprite spr, int posXO, int posYO, int larguraSpr, int alturaSpr){
    ALLEGRO_BITMAP* temp = NULL;
    temp = al_create_sub_bitmap(spr.Spritesheet,posXO,posYO,larguraSpr,alturaSpr);
    return temp;
}

void mudFrameSpr(Sprite *spr){
    spr->posFolX+=spr->larguraSpr;
    if(spr->posFolX==al_get_bitmap_width(spr->Spritesheet))
        spr->posFolX = 0;
}

#endif // SPRITE_H_INCLUDED
