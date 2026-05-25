#include "pendulo.h"
#include "FisicaHelper.h"

Pendulo::Pendulo() {
    plataforma = nullptr;
    barra = nullptr;
    bola = nullptr;
}

void Pendulo::crear(b2World& mundo, b2Body* plataformaRecibida) {

    plataforma = plataformaRecibida;

    b2BodyDef barraDef;
    barraDef.type = b2_dynamicBody;
    barraDef.position.Set(500 / SCALE, 350 / SCALE);

    barra = mundo.CreateBody(&barraDef);

    b2PolygonShape formaBarra;
    formaBarra.SetAsBox(8 / SCALE, 90 / SCALE);

    b2FixtureDef barraFix;
    barraFix.shape = &formaBarra;
    barraFix.density = 1.0f;
    barraFix.friction = 0.3f;

    barra->CreateFixture(&barraFix);

    b2BodyDef bolaDef;
    bolaDef.type = b2_dynamicBody;
    bolaDef.position.Set(500 / SCALE, 450 / SCALE);

    bola = mundo.CreateBody(&bolaDef);

    b2CircleShape formaBola;
    formaBola.m_radius = 25 / SCALE;

    b2FixtureDef bolaFix;
    bolaFix.shape = &formaBola;
    bolaFix.density = 2.0f;
    bolaFix.friction = 0.4f;
    bolaFix.restitution = 0.3f;

    bola->CreateFixture(&bolaFix);

    b2RevoluteJointDef unionGiro;
    unionGiro.Initialize(plataforma,barra,b2Vec2(500 / SCALE, 270 / SCALE));

    mundo.CreateJoint(&unionGiro);

    b2WeldJointDef unionFija;
    unionFija.Initialize(barra,bola,bola->GetWorldCenter());
    mundo.CreateJoint(&unionFija);

}

void Pendulo::dibujar() {

    Vector2 posPlataforma = convertirARaylib(plataforma->GetPosition());
    Vector2 posBarra = convertirARaylib(barra->GetPosition());
    Vector2 posBola = convertirARaylib(bola->GetPosition());

    dibujarCajaFisica(barra, 8 / SCALE, 90 / SCALE, BROWN);
    DrawCircle(posBola.x, posBola.y, 25, RED);

    DrawLine(posPlataforma.x, posPlataforma.y + 20, posBarra.x, posBarra.y, BLACK);

    DrawCircle(posPlataforma.x, posPlataforma.y + 20, 6, BLACK);

    DrawText("Revolute Joint", posPlataforma.x + 20, posPlataforma.y + 20, 14, BLACK);
    DrawText("Weld Joint", posBola.x + 30, posBola.y, 14, BLACK);
}