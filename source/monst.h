#ifndef MONST_H_INCLUDED
#define MONST_H_INCLUDED
#include "sprite.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MASCULINO 0
#define FEMININO 1

typedef struct{
    char *Nome;
    int Genero;
    long unsigned int contStatus;
    int Fome, Saude, Idade;
    int porcFome, porcSaude, porcIdade;
    int possibCagar;
    ALLEGRO_BITMAP* Poop;
    Sprite spr;
}Monstrinho;

Monstrinho iniMons(char nome[], int porcFome, int porcIdade, int porcSaude, char caminhoImagem[]){
    srand(time(NULL));
    Monstrinho temp;
    FILE *arq = fopen("save", "rb");
    if(arq){
        fread(&temp, sizeof(Monstrinho), 1, arq);
        temp.spr = iniSpr(256, 256, caminhoImagem, temp.spr.posFolX, temp.spr.posFolY);
    }
    else{
        temp.Nome = nome;
        temp.spr = iniSpr(256,256,caminhoImagem, 0, 0);
        temp.Poop = NULL;
        temp.Genero = rand()%2;
        temp.Idade = 0;
        temp.Fome = 0;
        temp.Saude = 100;
        temp.porcFome = porcFome;
        temp.porcIdade = porcIdade;
        temp.porcSaude = porcSaude;
        temp.possibCagar = 0;
    }
    temp.contStatus = 0;
    return temp;
}

void desenharMons(Monstrinho *monst){
    ALLEGRO_BITMAP *temp = pegarSprite(monst->spr, monst->spr.posFolX, monst->spr.posFolY, monst->spr.larguraSpr,monst->spr.alturaSpr);
    al_draw_scaled_bitmap(temp, 0, 0, al_get_bitmap_width(temp), al_get_bitmap_height(temp), 250, 165, 150, 150, 0);
    if(monst->Poop)
        al_draw_scaled_bitmap(monst->Poop, 0, 0, al_get_bitmap_width(monst->Poop), al_get_bitmap_height(monst->Poop), 165, 240, 100, 100, 0);
    mudFrameSpr(&monst->spr);
}

void alimentarMons(Monstrinho *monst){
    monst->Fome /= monst->porcFome;
    monst->possibCagar++;
    if(monst->Fome<0)
        monst->Fome = 0;
}

void tratarMons(Monstrinho *monst){
    monst->Saude += monst->porcSaude;
    if(monst->Saude>100)
        monst->Saude = 100;
}

void limpPoopMons(Monstrinho *monst){
    al_destroy_bitmap(monst->Poop);
    monst->Poop = NULL;
    monst->possibCagar = 0;
}

void envelhecerMons(Monstrinho *monst){
    monst->spr.posFolY += monst->spr.alturaSpr;
    monst->Idade = 0;
    monst->porcIdade *= 4;
}

void atualMons(Monstrinho *monst){
    if(monst->spr.posFolY!=768)
        monst->contStatus++;
    if(monst->contStatus % monst->porcFome == 0 && monst->spr.posFolY!=0 && monst->spr.posFolY!=768)
        monst->Fome++;
    if(monst->contStatus % monst->porcIdade == 0  && monst->spr.posFolY!=768){
        monst->Idade++;
        if(monst->Idade == 100)
            envelhecerMons(monst);
    }
    if(monst->contStatus % monst->porcSaude == 0 && monst->spr.posFolY!=0 && monst->spr.posFolY!=768)
        monst->Saude--;
    if(monst->possibCagar == 3){
        monst->Poop = al_load_bitmap("images/poop.png");
        al_convert_mask_to_alpha(monst->Poop, al_map_rgb(0, 255, 0));
    }
    if(monst->Saude == -50 || monst->Fome == 150)
        monst->spr.posFolY += (al_get_bitmap_height(monst->spr.Spritesheet) - monst->spr.alturaSpr) - monst->spr.posFolY;
}

void finalizarMonst(Monstrinho *monst){
    FILE *arq = fopen("save", "wb");
    if(arq)
        fwrite(monst, sizeof(Monstrinho), 1, arq);
    if(monst->spr.Spritesheet)
        al_destroy_bitmap(monst->spr.Spritesheet);
    if(monst->Poop)
        al_destroy_bitmap(monst->Poop);
}

#endif // MONST_H_INCLUDED
