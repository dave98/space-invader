#include <allegro.h>
#include "inicia.h"
#include "disparos.h"
#include "personajes.h"
#include "diseno.h"
#include <stdlib.h>
#include <time.h>

#define ANCHO 600
#define ALTO  600

bool limite(struct NAVE E[], int& dir){
    for(int i = 0; i<55; i++){
        if((E[i].x > 520 || E[i].x< 50) && E[i].vida){
            dir = -1*dir;
            return true;
        }
    }
    return false;
}

void mover_enemigos(struct NAVE E[], int& mov, int& dir){
    for(int i = 0; i<55; ++i){
        E[i].x += dir;
    }
    if(++mov == 2) mov = 0;
                //if(E[0].temporizador(10))
    if(limite(E, dir)){
        for(int j=0; j<55; j++) E[j].y += 10;
    }

}




int main(){
    srand(time(NULL));
    inicia_allegro(ANCHO,ALTO); // fuciones del include inicia.h
	inicia_audio(70,270);        //

    BITMAP *buffer = create_bitmap(ANCHO, ALTO);
    BITMAP *portada = load_bitmap("Recursos/portada.bmp", NULL);
    BITMAP *fondo = load_bitmap("Recursos/fondo.bmp", NULL);
    BITMAP *img_muros = load_bitmap("Recursos/escudos.bmp", NULL);
    MIDI* musica_fondo = load_midi("Recursos/arena.wav.mid");

    play_midi(musica_fondo, 1);
    PORTADA(portada);

    NAVE N;
    N.inicia("Recursos/nave.bmp", "Recursos/Bala2.bmp", 6, 12, 30, 20, ANCHO/2, ALTO-70, -8, 0, 3, "Recursos/0.wav", "Recursos/15.wav");
    NAVE E[60];
    acomoda_enemigos(E);
    Balas disparos[N.max_disp];//indica la cantidad max de disparos
    Balas disp_E[E[0].max_disp];

    escudo ES[30];
    iniciar_escudo(ES);

    int azar = rand()%55;
    int mov =0, dir = -5;
    int vel_juego = 10;

    while(!key[KEY_ESC]){

        clear_to_color(buffer, 0x000000);
        pintar_escudo(ES, img_muros, buffer);

        if(E[0].temporizador(vel_juego))
            mover_enemigos(E, mov, dir);

        N.pinta(buffer, 0, 0);
        N.mueve();
        crear_bala_nave(N, disparos);

        N.dispara(disparos, buffer);

        for (int i = 0 ; i<55; i++){
            if(elimina_bala_objeto(N, E[i], disparos))
                explosion1(E[i], buffer);
        }
        elimina_bala_escudo(N,ES, disparos);

        pintar_enemigo(E, buffer, mov);
        crear_bala_enemigo(E, azar);

        E[azar].dispara(disp_E, buffer);
        if(elimina_bala_objeto(E[azar], N, disp_E))
            explosion2(N, buffer, fondo);
            elimina_bala_escudo(E[azar], ES, disp_E);
        imprimir_fondo(fondo, buffer);
        blit(buffer, screen, 0, 0, 0, 0, ANCHO, ALTO);
        rest(20);
    }


	return 0;
}
END_OF_MAIN();

