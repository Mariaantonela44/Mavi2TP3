#include "FisicaHelper.h"

const float SCALE = 30.0f;

Vector2 convertirARaylib(b2Vec2 posicion) {

    Vector2 posicionPantalla;

    posicionPantalla.x = posicion.x * SCALE;
    posicionPantalla.y = posicion.y * SCALE;

    return posicionPantalla;
}

void dibujarCajaFisica(b2Body* cuerpo,float ancho,float alto,Color color) {

    Vector2 posicion =convertirARaylib(cuerpo->GetPosition());

    Rectangle rectangulo;

    rectangulo.x = posicion.x;
    rectangulo.y = posicion.y;

    rectangulo.width =ancho * SCALE * 2;

    rectangulo.height = alto * SCALE * 2;

    Vector2 centro;

    centro.x = ancho * SCALE;
    centro.y = alto * SCALE;

    DrawRectanglePro(rectangulo,centro,cuerpo->GetAngle() * RAD2DEG,color);
}