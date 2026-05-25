#include "caja.h"
#include "FisicaHelper.h"

void Caja::crear(b2World& mundo) {

    for (int fila = 0; fila < 4; fila++) {

        for (int columna = 0; columna < 4 - fila; columna++) {

            float x = 700 + columna * 40 + fila * 20;
            float y = 500 - fila * 40;

            b2BodyDef cajaDef;
            cajaDef.type = b2_dynamicBody;

            cajaDef.position.Set(x / SCALE,y / SCALE);

            b2Body* caja =mundo.CreateBody(&cajaDef);

            b2PolygonShape formaCaja;

            formaCaja.SetAsBox(15 / SCALE,15 / SCALE);

            b2FixtureDef fixture;

            fixture.shape = &formaCaja;
            fixture.density = 1.0f;
            fixture.friction = 0.5f;
            fixture.restitution = 0.2f;

            caja->CreateFixture(&fixture);

            cuerpos.push_back(caja);
        }
    }
}

void Caja::dibujar() {

    for (int i = 0; i < cuerpos.size(); i++) {
        dibujarCajaFisica(cuerpos[i],15 / SCALE,15 / SCALE,ORANGE);
    }
}