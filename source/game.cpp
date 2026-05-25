#include "game.h"
#include "FisicaHelper.h"

Game::Game() : mundo(b2Vec2(0.0f, 9.8f)) {

    colorFondo = { 230, 215, 255, 255 };

    suelo = nullptr;
    paredIzquierda = nullptr;
    paredDerecha = nullptr;
}

void Game::ejecutar() {

    InitWindow(1000, 600, "Laboratorio Mecanico de Mavix");
    SetTargetFPS(60);

    iniciar();

    while (!WindowShouldClose()) {
        actualizar();
        dibujar();
    }

    CloseWindow();
}

void Game::iniciar() {

    crearSuelo();
    crearParedes();
    elevador.crear(mundo, 80, 200);
    plataforma.crear(mundo);
    pendulo.crear(mundo, plataforma.getCuerpo());
    penduloMovible.crear(mundo, 800, 100);
    resorte.crear(mundo);
    cajas.crear(mundo);

}

void Game::crearSuelo() {

    b2BodyDef sueloDef;
    sueloDef.position.Set(500 / SCALE, 550 / SCALE);

    suelo = mundo.CreateBody(&sueloDef);

    b2PolygonShape formaSuelo;
    formaSuelo.SetAsBox(400 / SCALE, 10 / SCALE);

    suelo->CreateFixture(&formaSuelo, 0.0f);
}

void Game::crearParedes() {

    b2BodyDef paredIzqDef;
    paredIzqDef.position.Set(20 / SCALE, 300 / SCALE);

    paredIzquierda = mundo.CreateBody(&paredIzqDef);

    b2PolygonShape formaParedIzq;
    formaParedIzq.SetAsBox(10 / SCALE, 300 / SCALE);

    paredIzquierda->CreateFixture(&formaParedIzq, 0.0f);

    b2BodyDef paredDerDef;
    paredDerDef.position.Set(980 / SCALE, 300 / SCALE);

    paredDerecha = mundo.CreateBody(&paredDerDef);

    b2PolygonShape formaParedDer;
    formaParedDer.SetAsBox(10 / SCALE, 300 / SCALE);

    paredDerecha->CreateFixture(&formaParedDer, 0.0f);
}

void Game::actualizar() {


    penduloMovible.actualizar();

    mundo.Step(1.0f / 60.0f, 8, 3);

    plataforma.actualizar();

    elevador.actualizar();
}

void Game::dibujar() {

    BeginDrawing();

    DrawRectangleGradientV(0,0,1000,600,Color{ 240, 220, 255, 255 },Color{ 200, 170, 255, 255 });

    DrawText("Laboratorio Mecanico de Mavix", 20, 20, 24, BLACK);
    DrawText("SPACE = balancear pendulo", 20, 55, 18, BLACK);

    DrawRectangle(100, 540, 800, 20, DARKGRAY);

    DrawRectangle(0, 0, 20, 600, DARKGRAY);
    DrawRectangle(980, 0, 20, 600, DARKGRAY);

    plataforma.dibujar();
    pendulo.dibujar();
    elevador.dibujar();
    penduloMovible.dibujar();
    resorte.dibujar();
    cajas.dibujar();

    EndDrawing();
}