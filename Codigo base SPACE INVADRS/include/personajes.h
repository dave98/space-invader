#include<allegro.h>

#ifndef PERSONAJES_H
#define PERSONAJES_H


struct NAVE{
    int x, y;
    int n_disp;
    int max_disp;
    int tick;
    int ancho_b, alto_b;
    int ancho_p, alto_p;
    int dir_bala;
    int tipo;
    int vida;

    BITMAP* img_nav;
    BITMAP* img_bala;
    BITMAP* exp_enem;
    SAMPLE* disparo;
    SAMPLE* explo;

    void inicia(char* ruta_nave, char* ruta_bala, int _ancho_b, int _alto_b,
                int _ancho_p, int _alto_p, int _x, int _y, int _dir_bala, int _tipo, int vida, char* m_disp, char* m_exp);
    bool temporizador(int tiempo);
    void pinta(BITMAP* buffer, int ix, int iy);
    void mueve();
    void dispara(struct Balas disparos[], BITMAP* buffer);
};

void acomoda_enemigos(struct NAVE E[]);
void pintar_enemigo(struct NAVE E[], BITMAP* buffer, int mov);
void explosion1(struct NAVE E, BITMAP* buffer);
void explosion2(struct NAVE N, BITMAP* buffer, BITMAP* fondo);
void crear_bala_enemigo(struct NAVE E[], int &azar);
void crear_bala_nave(struct NAVE& N, struct Balas disparos[]);

struct escudo{
    int x, y;
    int dan;
    int tipo;

};

void iniciar_escudo(struct escudo muros[]);
void pintar_escudo (struct escudo ES[], BITMAP* img_mur, BITMAP* buffer);



#endif // PERSONAJES_H
