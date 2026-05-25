#include "pendulofijo.h"
#include "FisicaHelper.h"


PenduloMovible::PenduloMovible() {
    base = nullptr;
    barra = nullptr;
    bola = nullptr;
    golpeHaciaDerecha = true;
}

void PenduloMovible::crear(b2World& mundo, float x, float y) {

    // Base fija
    b2BodyDef baseDef;
    baseDef.position.Set(x / SCALE, y / SCALE);

    base = mundo.CreateBody(&baseDef);

    b2PolygonShape formaBase;
    formaBase.SetAsBox(45 / SCALE, 12 / SCALE);

    base->CreateFixture(&formaBase, 0.0f);

    // Barra
    b2BodyDef barraDef;
    barraDef.type = b2_dynamicBody;
    barraDef.position.Set(x / SCALE, (y + 90) / SCALE);

    barra = mundo.CreateBody(&barraDef);

    b2PolygonShape formaBarra;
    formaBarra.SetAsBox(6 / SCALE, 80 / SCALE);

    b2FixtureDef barraFix;
    barraFix.shape = &formaBarra;
    barraFix.density = 1.0f;
    barraFix.friction = 0.3f;

    barra->CreateFixture(&barraFix);

    // Bola
    b2BodyDef bolaDef;
    bolaDef.type = b2_dynamicBody;
    bolaDef.position.Set(x / SCALE, (y + 180) / SCALE);

    bola = mundo.CreateBody(&bolaDef);

    b2CircleShape formaBola;
    formaBola.m_radius = 22 / SCALE;

    b2FixtureDef bolaFix;
    bolaFix.shape = &formaBola;
    bolaFix.density = 2.0f;
    bolaFix.friction = 0.4f;
    bolaFix.restitution = 0.3f;

    bola->CreateFixture(&bolaFix);

    // Unión giratoria base-barra
    b2RevoluteJointDef unionGiro;
    unionGiro.Initialize(base,barra,b2Vec2(x / SCALE, (y + 20) / SCALE));
    mundo.CreateJoint(&unionGiro);

    // Unión fija barra-bola
    b2WeldJointDef unionFija;
    unionFija.Initialize(barra,bola,bola->GetWorldCenter());
    mundo.CreateJoint(&unionFija);
}

void PenduloMovible::actualizar() {

    if (IsKeyPressed(KEY_SPACE)) {

        if (golpeHaciaDerecha) {
            bola->ApplyLinearImpulseToCenter(b2Vec2(18.0f, 0.0f),true);
        }
        else {
            bola->ApplyLinearImpulseToCenter(b2Vec2(-18.0f, 0.0f),true);
        }

        golpeHaciaDerecha = !golpeHaciaDerecha;
    }
}

void PenduloMovible::dibujar() {

    Vector2 posBase = convertirARaylib(base->GetPosition());
    Vector2 posBarra = convertirARaylib(barra->GetPosition());
    Vector2 posBola = convertirARaylib(bola->GetPosition());

    DrawRectangle(posBase.x - 45, posBase.y - 12, 90, 24, DARKPURPLE);

    dibujarCajaFisica(barra, 6 / SCALE, 80 / SCALE, BROWN);

    DrawCircle(posBola.x, posBola.y, 22, RED);

    DrawLine(posBase.x, posBase.y + 20, posBarra.x, posBarra.y, BLACK);

    DrawCircle(posBase.x, posBase.y + 20, 6, BLACK);

    DrawText("Pendulo fijo", posBase.x - 40, posBase.y - 35, 14, BLACK);
}