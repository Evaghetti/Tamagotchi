#ifndef PREP_H_INCLUDED
#define PREP_H_INCLUDED

#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include "menu.h"
#include "monst.h"

#define FPS 5.0

ALLEGRO_DISPLAY* window = NULL;
ALLEGRO_EVENT_QUEUE *ListaEv = NULL;
ALLEGRO_TIMER *timer = NULL;
ALLEGRO_FONT *fonte = NULL;
Menu menu[5];
Monstrinho monst;

void mensErro(char frase[]){//recebe uma string
    al_show_native_message_box(window,"ERRO","Ocorreu um Erro",frase,NULL,ALLEGRO_MESSAGEBOX_ERROR);
}

int init(){
    int i;
    if(!al_init()){
        mensErro("Erro ao iniciar o Allegro");
        return 0;
    }
    window = al_create_display(640,480);
    if(!window){
        mensErro("Erro ao Criar a Janela");
        return 0;
    }
    al_set_window_title(window,"Tamabro");
    timer = al_create_timer(1/FPS);
    if(!timer){
        mensErro("Erro ao comecar os timers");
        return 0;
    }
    if(!al_init_image_addon()){
        mensErro("Erro ao iniciar addon de imagem");
        return 0;
    }
    al_init_font_addon();
    if(!al_init_ttf_addon()){
        mensErro("Erro ao inicializar o addon de True Type Fonts");
        return 0;
    }
    fonte = al_load_font("fonts/digital-7.ttf", 50, 0);
    if(!fonte){
        mensErro("Erro ao Carregar a fonte Digital - 7");
        return 0;
    }
    if(!al_install_mouse()){
        mensErro("Erro ao instalar ponteiro do mouse");
        return 0;
    }
    ListaEv = al_create_event_queue();
    if(!ListaEv){
        mensErro("Erro ao criar lista de eventos");
        return 0;
    }
    for(i = 0; i<5; i++){
        if(i < 3)
            menu[i] = initMenu("images/Menu.png", 213*i, 5, 256, 256, 256*i, 0, 213, 150);
        else
            menu[i] = initMenu("images/Menu.png",213*(i-2.5),325,256,256,256*i,0,213,150);
        if(!menu[i].sprite || !menu[i].sprsheet.Spritesheet){
            mensErro("Erro ao abrir as imagens para o menu.");
            return 0;
        }
    }
    monst = iniMons("Fulano", 8, 4, 20,"images/monst_sprsh.png");
    if(!monst.spr.Spritesheet){
        mensErro("Erro ao abrir alguma imagem do Tamabro");
        return 0;
    }
    al_start_timer(timer);
    al_register_event_source(ListaEv,al_get_display_event_source(window));
    al_register_event_source(ListaEv,al_get_mouse_event_source());
    al_register_event_source(ListaEv,al_get_timer_event_source(timer));
    return 1;
}

void finalizar(){
    int i;
    if(window)
        al_destroy_display(window);
    if(ListaEv)
        al_destroy_event_queue(ListaEv);
    if(timer)
        al_destroy_timer(timer);
    if(fonte)
        al_destroy_font(fonte);
    for(i = 0; i<5; i++){
       if(menu[i].sprsheet.Spritesheet)
            finalizarMenu(&menu[i]);
    }
    finalizarMonst(&monst);
}

#endif // PREP_H_INCLUDED
