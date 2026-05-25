#ifndef GAME_H
#define GAME_H

#include "raylib.h"
#include <box2d.h>

#include "Plataforma.h"
#include "pendulo.h"
#include "resorte.h"
#include "caja.h"
#include "pendulofijo.h"
#include "elevador.h"

class Game {
private:
    b2World mundo;
    Color colorFondo;
    b2Body* suelo;
    Elevador elevador;
    Plataforma plataforma;
    Pendulo pendulo;
    Resorte resorte;
    Caja cajas;
    PenduloMovible penduloMovible;
    b2Body* paredIzquierda;
    b2Body* paredDerecha;
    void crearParedes();
    void iniciar();
    void crearSuelo();
    void actualizar();
    void dibujar();

public:
    Game();
    void ejecutar();
};

#endif 

