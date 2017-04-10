#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "monst.h"
#include "prep.h"

typedef struct{
    int x, y;
    int larguraBot, alturaBot;
    ALLEGRO_BITMAP *sprite;
    Sprite sprsheet;
}Menu;

Menu initMenu(char camIm[], int x, int y, int larSpr, int altSpr, int posXO, int posYO, int larBot, int altBot){
    Menu temp;
    temp.x = x;
    temp.y = y;
    temp.sprsheet = iniSpr(larSpr, altSpr, camIm , 0, 0);
    temp.sprite = pegarSprite(temp.sprsheet, posXO, posYO, temp.sprsheet.larguraSpr, temp.sprsheet.alturaSpr);
    temp.larguraBot = larBot;
    temp.alturaBot = altBot;
    return temp;
}

void desenharMenu(Menu menu[], ALLEGRO_DISPLAY *janela){
    int i;
    ALLEGRO_BITMAP *Quadrado = al_create_bitmap(menu[0].larguraBot,menu[0].alturaBot);//cria um bitmap vazio com o tamanho do botão.
    for(i = 0; i<5; i++){
        al_set_target_bitmap(Quadrado);
        al_clear_to_color(al_map_rgb(0 ,0 ,0));
        al_set_target_backbuffer(janela);
        al_draw_bitmap(Quadrado,menu[i].x,menu[i].y,0);
    }
    Quadrado = al_create_bitmap(menu[0].larguraBot-(menu[0].larguraBot*0.040),menu[0].alturaBot-(menu[0].alturaBot*0.040));
    for(i = 0; i<5; i++){
        al_set_target_bitmap(Quadrado);
        al_clear_to_color(al_map_rgb(255, 255, 255));
        al_set_target_backbuffer(janela);
        al_draw_bitmap(Quadrado,menu[i].x+(menu[0].larguraBot*0.025),menu[i].y+(menu[0].alturaBot*0.025),0);
    }
    for(i = 0; i<5; i++)
        al_draw_scaled_bitmap(menu[i].sprite,0,0,menu[i].sprsheet.larguraSpr,menu[i].sprsheet.alturaSpr,menu[i].x,menu[i].y,menu[i].larguraBot,menu[i].alturaBot,0);//desenho todos os botões do menu
    al_destroy_bitmap(Quadrado);
}

void status(int *sair, ALLEGRO_EVENT_QUEUE* ListaEv, ALLEGRO_DISPLAY* janela, ALLEGRO_FONT* fonte, Monstrinho monst){
    int menu = 1;
    al_flush_event_queue(ListaEv);
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP* Sair = al_create_bitmap(100, 100);
    al_set_target_bitmap(Sair);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_set_target_backbuffer(janela);
    al_clear_to_color(al_map_rgb(235, 235, 235));
    while(*sair == 0 && menu == 1){
        al_wait_for_event(ListaEv, &evento);
        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            *sair = 1;
        else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(evento.mouse.x >= 0 && evento.mouse.x <= 100){
                if(evento.mouse.y >= 380 && evento.mouse.y <= 480)
                    menu = 0;
            }
        }
        al_clear_to_color(al_map_rgb(235, 235, 235));
        al_draw_textf(fonte, al_map_rgb( 0, 0, 0), 250, 160, 0, "Fome: %d %", monst.Fome);
        al_draw_textf(fonte, al_map_rgb( 0, 0, 0), 250, 220, 0, "Saude: %d %", monst.Saude);
        al_draw_textf(fonte, al_map_rgb( 0, 0, 0), 250, 280, 0, "Idade: %d %", monst.Idade);
        al_draw_bitmap(Sair, 0, 380, 0);
        al_flip_display();
    }
}

void infomacoes(int *sair, ALLEGRO_EVENT_QUEUE* ListaEv, ALLEGRO_DISPLAY* janela, ALLEGRO_FONT* fonte, Monstrinho monst){
    int menu = 1;
    char *fase;
    if(monst.spr.posFolY==0)
        fase = "Ovo";
    else if(monst.spr.posFolY==256)
        fase = "Crianca";
    else if(monst.spr.posFolY==512)
        fase = "Adulto";
    else
        fase = "Morto";
    al_flush_event_queue(ListaEv);
    ALLEGRO_EVENT evento;
    ALLEGRO_BITMAP* Sair = al_create_bitmap(100,100);
    al_set_target_bitmap(Sair);
    al_clear_to_color(al_map_rgb(255, 0, 0));
    al_set_target_backbuffer(janela);
    al_clear_to_color(al_map_rgb(235, 235, 235));
    while(*sair == 0 && menu == 1){
        al_wait_for_event(ListaEv, &evento);
        if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            *sair = 1;
        else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(evento.mouse.x >= 0 && evento.mouse.x <= 100){
                if(evento.mouse.y >= 380 && evento.mouse.y <= 480)
                    menu = 0;
            }
        }
        al_clear_to_color(al_map_rgb(235,235,235));
        al_draw_textf(fonte, al_map_rgb( 0, 0, 0), 200, 160, 0, "Nome: %s",monst.Nome);
        al_draw_textf(fonte, al_map_rgb( 0, 0, 0), 200, 220, 0, "Genero: %s",(monst.Genero==0)?"Masculino":"Feminino");
        al_draw_textf(fonte, al_map_rgb( 0, 0, 0), 200, 280, 0, "Fase: %s", fase);
        al_draw_bitmap(Sair, 0, 380, 0);
        al_flip_display();
    }
}

void finalizarMenu(Menu *menu){
    if(menu->sprsheet.Spritesheet)
        al_destroy_bitmap(menu->sprsheet.Spritesheet);
    if(menu->sprite)
        al_destroy_bitmap(menu->sprite);
}

#endif // MENU_H_INCLUDED
