#include "source/prep.h"

int main(){
    if(init() == 0){
        finalizar();
        return 1;
    }
    int i, op = 0, desenha = 0, sair = 0;
    while(sair == 0){
        ALLEGRO_EVENT evento;
        al_wait_for_event(ListaEv, &evento);
        if(evento.type == ALLEGRO_EVENT_TIMER){
            atualMons(&monst);
            desenha = 1;
        }
        else if(evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            sair = 1;
        else if(evento.type == ALLEGRO_EVENT_MOUSE_AXES){
            for(i = 0; i<5;i++){
                if(evento.mouse.x >= menu[i].x && evento.mouse.x <= menu[i].larguraBot + menu[i].x){
                    if(evento.mouse.y >= menu[i].y && evento.mouse.y <= menu[i].alturaBot + menu[i].y){
                        op = i;
                        break;
                    }
                }
                op = 6;
            }
        }
        else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
            if(op == 0 && monst.spr.posFolY != 0 && monst.spr.posFolY != 768)
                alimentarMons(&monst);
            else if(op == 1 && monst.spr.posFolY != 0 && monst.spr.posFolY != 768)
                tratarMons(&monst);
            else if(op == 2 && monst.spr.posFolY != 0 && monst.spr.posFolY != 768)
                limpPoopMons(&monst);
            else if(op == 3)
                status(&sair, ListaEv, window, fonte, monst);
            else if(op == 4)
                infomacoes(&sair, ListaEv, window, fonte, monst);
        }
        if(al_is_event_queue_empty(ListaEv) && desenha==1){
            al_clear_to_color(al_map_rgb(235,235,235));
            desenharMenu(menu, window);
            desenharMons(&monst);
            al_flip_display();
            desenha = 0;
        }
    }
    finalizar();
    return 0;
}
