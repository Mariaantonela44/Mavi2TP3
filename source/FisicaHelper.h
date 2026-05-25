#ifndef FISICAHELPER_H
#define FISICAHELPER_H


#include "raylib.h"
#include <box2d.h>

extern const float SCALE;

Vector2 convertirARaylib(b2Vec2 posicion);

void dibujarCajaFisica(
    b2Body* cuerpo,
    float ancho,
    float alto,
    Color color
);
#endif