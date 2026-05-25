#ifndef ELEVADOR_H
#define ELEVADOR_H

#include "raylib.h"
#include <box2d.h>

class Elevador {
private:
    b2Body* soporte;
    b2Body* plataforma;
    b2PrismaticJoint* movimiento;

public:
    Elevador();
    void crear(b2World& mundo, float x, float y);
    void actualizar();
    void dibujar();
};
#endif