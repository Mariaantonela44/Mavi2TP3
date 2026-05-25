#ifndef CAJA_H
#define CAJA_H

#include "raylib.h"
#include <box2d.h>
#include <vector>

class Caja {
private:
    std::vector<b2Body*> cuerpos;

public:
    void crear(b2World& mundo);
    void dibujar();
};
#endif