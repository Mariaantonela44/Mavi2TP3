#include "resorte.h"
#include "FisicaHelper.h"

Resorte::Resorte() {
    ancla = nullptr;
    peso = nullptr;
}

void Resorte::crear(b2World& mundo) {

    b2BodyDef anclaDef;
    anclaDef.position.Set(200 / SCALE, 180 / SCALE);

    ancla = mundo.CreateBody(&anclaDef);

    b2PolygonShape formaAncla;
    formaAncla.SetAsBox(25 / SCALE, 10 / SCALE);

    ancla->CreateFixture(&formaAncla, 0.0f);

    b2BodyDef pesoDef;
    pesoDef.type = b2_dynamicBody;
    pesoDef.position.Set(200 / SCALE, 320 / SCALE);

    peso = mundo.CreateBody(&pesoDef);

    b2PolygonShape formaPeso;
    formaPeso.SetAsBox(25 / SCALE, 25 / SCALE);

    b2FixtureDef pesoFix;
    pesoFix.shape = &formaPeso;
    pesoFix.density = 2.0f;
    pesoFix.friction = 0.4f;
    pesoFix.restitution = 0.2f;

    peso->CreateFixture(&pesoFix);

    b2DistanceJointDef resorteDef;
    resorteDef.Initialize(ancla,peso,ancla->GetWorldCenter(),peso->GetWorldCenter());
    resorteDef.length = 120 / SCALE;
    resorteDef.stiffness = 4.0f;
    resorteDef.damping = 0.5f;

    mundo.CreateJoint(&resorteDef);
}

void Resorte::dibujar() {

    Vector2 posAncla = convertirARaylib(ancla->GetPosition());
    Vector2 posPeso = convertirARaylib(peso->GetPosition());

    DrawRectangle(posAncla.x - 25, posAncla.y - 10, 50, 20, DARKGRAY);
    DrawLine(posAncla.x, posAncla.y, posPeso.x, posPeso.y, DARKGREEN);

    dibujarCajaFisica(peso, 25 / SCALE, 25 / SCALE, GREEN);

    DrawText("Distance Joint", posPeso.x + 30, posPeso.y, 14, DARKGREEN);
}