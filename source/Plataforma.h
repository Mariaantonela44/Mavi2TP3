#ifndef PLATAFORMA_H
#define PLATAFORMA_H

#include "raylib.h"
#include <box2d.h>

class Plataforma {
private:
    b2Body* soporte;
    b2Body* cuerpo;
    b2PrismaticJoint* movimiento;

public:
    Plataforma();
    void crear(b2World& mundo);
    void actualizar();
    void dibujar();

    b2Body* getCuerpo();
};

#endif 