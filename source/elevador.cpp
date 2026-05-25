#include "elevador.h"
#include "FisicaHelper.h"

Elevador::Elevador() {
    soporte = nullptr;
    plataforma = nullptr;
    movimiento = nullptr;
}

void Elevador::crear(b2World& mundo, float x, float y) {

    // soporte fijo
    b2BodyDef soporteDef;
    soporteDef.position.Set(x / SCALE, y / SCALE);

    soporte = mundo.CreateBody(&soporteDef);

    b2PolygonShape formaSoporte;
    formaSoporte.SetAsBox(50 / SCALE, 10 / SCALE);

    soporte->CreateFixture(&formaSoporte, 0.0f);

    // plataforma que sube y baja
    b2BodyDef plataformaDef;
    plataformaDef.type = b2_dynamicBody;
    plataformaDef.position.Set(x / SCALE, (y + 120) / SCALE);

    plataforma = mundo.CreateBody(&plataformaDef);

    b2PolygonShape formaPlataforma;
    formaPlataforma.SetAsBox(40 / SCALE, 15 / SCALE);

    b2FixtureDef plataformaFix;
    plataformaFix.shape = &formaPlataforma;
    plataformaFix.density = 1.0f;
    plataformaFix.friction = 0.5f;

    plataforma->CreateFixture(&plataformaFix);

    // joint vertical
    b2PrismaticJointDef jointDef;
    jointDef.Initialize(soporte,plataforma,plataforma->GetWorldCenter(),b2Vec2(0.0f, 1.0f));

    jointDef.enableLimit = true;
    jointDef.lowerTranslation = 0.0f;
    jointDef.upperTranslation = 4.0;
    jointDef.enableMotor = true;
    jointDef.motorSpeed = 2.0f;
    jointDef.maxMotorForce = 800.0f;

    movimiento = (b2PrismaticJoint*)mundo.CreateJoint(&jointDef);
}

void Elevador::actualizar() {

    float posicion = movimiento->GetJointTranslation();

    if (posicion > 3.8f) {
        movimiento->SetMotorSpeed(-2.0f);
    }

    if (posicion < 0.2f) {
        movimiento->SetMotorSpeed(2.0f);
    }
}

void Elevador::dibujar() {

    Vector2 posSoporte = convertirARaylib(soporte->GetPosition());
    Vector2 posPlataforma = convertirARaylib(plataforma->GetPosition());

    DrawRectangle(posSoporte.x - 50, posSoporte.y - 10, 100, 20, DARKGRAY);

    DrawLine(posSoporte.x, posSoporte.y, posPlataforma.x, posPlataforma.y, DARKGREEN);

    dibujarCajaFisica(plataforma, 40 / SCALE, 15 / SCALE, GREEN);

    DrawText("Elevador", posSoporte.x - 35, posSoporte.y - 30, 14, BLACK);
}