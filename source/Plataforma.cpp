#include "Plataforma.h"
#include "FisicaHelper.h"

Plataforma::Plataforma() {
    soporte = nullptr;
    cuerpo = nullptr;
    movimiento = nullptr;
}

void Plataforma::crear(b2World& mundo) {

    b2BodyDef soporteDef;
    soporteDef.position.Set(500 / SCALE, 150 / SCALE);

    soporte = mundo.CreateBody(&soporteDef);

    b2PolygonShape formaSoporte;
    formaSoporte.SetAsBox(120 / SCALE, 10 / SCALE);
    soporte->CreateFixture(&formaSoporte, 0.0f);

    b2BodyDef plataformaDef;
    plataformaDef.type = b2_dynamicBody;
    plataformaDef.position.Set(500 / SCALE, 250 / SCALE);

    cuerpo = mundo.CreateBody(&plataformaDef);

    b2PolygonShape formaPlataforma;
    formaPlataforma.SetAsBox(80 / SCALE, 15 / SCALE);

    b2FixtureDef fixture;
    fixture.shape = &formaPlataforma;
    fixture.density = 1.0f;
    fixture.friction = 0.4f;

    cuerpo->CreateFixture(&fixture);

    b2PrismaticJointDef jointDef;
    jointDef.Initialize(
        soporte,
        cuerpo,
        cuerpo->GetWorldCenter(),
        b2Vec2(1.0f, 0.0f)
    );

    jointDef.enableLimit = true;
    jointDef.lowerTranslation = -3.0f;
    jointDef.upperTranslation = 3.0f;

    jointDef.enableMotor = true;
    jointDef.motorSpeed = 2.0f;
    jointDef.maxMotorForce = 1000.0f;

    movimiento = (b2PrismaticJoint*)mundo.CreateJoint(&jointDef);
}

void Plataforma::actualizar() {

    float posicion = movimiento->GetJointTranslation();

    if (posicion > 2.8f) {
        movimiento->SetMotorSpeed(-2.0f);
    }

    if (posicion < -2.8f) {
        movimiento->SetMotorSpeed(2.0f);
    }
}

void Plataforma::dibujar() {

    Vector2 posSoporte = convertirARaylib(soporte->GetPosition());
    Vector2 posPlataforma = convertirARaylib(cuerpo->GetPosition());

    DrawRectangle(posSoporte.x - 120, posSoporte.y - 10, 240, 20, GRAY);
    DrawRectangle(posPlataforma.x - 80, posPlataforma.y - 15, 160, 30, BLUE);

    DrawText("Prismatic Joint", posPlataforma.x - 60, posPlataforma.y - 50, 14, BLACK);
}

b2Body* Plataforma::getCuerpo() {
    return cuerpo;
}