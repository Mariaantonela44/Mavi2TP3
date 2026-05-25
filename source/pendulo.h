#ifndef PENDULO_H
#define PENDULO_H

#include "raylib.h"
#include <box2d.h>

class Pendulo {
private:
    b2Body* plataforma;
    b2Body* barra;
    b2Body* bola;

public:
    Pendulo();

    void crear(b2World& mundo, b2Body* plataformaRecibida);
    void dibujar();
};
#endif