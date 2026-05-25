#ifndef RESORTE_H
#define RESORTE_H

#include "raylib.h"
#include <box2d.h>

class Resorte {

private:
    b2Body* ancla;
    b2Body* peso;

public:
    Resorte();
    void crear(b2World& mundo);
    void dibujar();
};

#endif