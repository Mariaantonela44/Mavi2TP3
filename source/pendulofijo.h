#ifndef PENDULOFIJO_H
#define PENDULOFIJO_H


#include "raylib.h"
#include <box2d.h>

class PenduloMovible {
private:
    b2Body* base;
    b2Body* barra;
    b2Body* bola;
    bool golpeHaciaDerecha;


public:
    PenduloMovible();
    void crear(b2World& mundo, float x, float y);
    void actualizar();
    void dibujar();
};
#endif