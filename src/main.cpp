#include "../include/raylib.h"
#include "../include/rcamera.h"
#include "../include/raymath.h"
#include "../include/walls.h"
#include "../include/particle.h"
#include <iostream>

using namespace std;

#define CAMERA_MOVE_SPEED 0.09f
#define CAMERA_ROTATION_SPEED 0.03f
#define CAMERA_PAN_SPEED 0.2f

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.001f // TODO: it should be independant of framerate

// Camera orbital speed in CAMERA_ORBITAL mode
#define CAMERA_ORBITAL_SPEED 0.5f // Radians per second

void UpdateCamera2(Camera *camera, int mode);
void drawWalls(Wall walls);

int main(void)
{

    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    InitWindow(screenWidth, screenHeight, "Testing particles");
    Wall walls;

    Particle particles[MAX_PARTICLES];

    int particleCount = initializeParticles(particles);
    float frameTime = GetFrameTime();
    walls.wallPositionTop = {0.0f, 50.0f, 0.0f};
    walls.wallPositionBottom = {0.0f, -50.0f, 0.0f};

    walls.wallPositionInFront = {50.0f, 0.0f, 0.0f};
    walls.wallPositionBehind = {-50.0f, 0.0f, 0.0f};

    walls.wallPositionLeft = {-0.0f, 0.0f, -50.0f};
    walls.wallPositionRight = {0.0f, 0.0f, 50.0f};

    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 0.0f, 0.0f};
    camera.target = (Vector3){1.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 90.0f;

    DisableCursor();

    SetTargetFPS(165);

    while (!WindowShouldClose())
    {
        frameTime = GetFrameTime();
        UpdateCamera2(&camera, CAMERA_FREE);
        BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

        drawParticles(particles, particleCount);
        UpdateParticlesPosition(particles, particleCount, frameTime);

        drawWalls(walls);
        DrawCubeWires({0.0f, 0.0f, 0.0f}, 2.0f, 2.0f, 2.0f, WHITE);
        DrawGrid(10, 1.0f);
        EndMode3D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}

void UpdateCamera2(Camera *camera, int mode)
{
    Vector2 mousePositionDelta = GetMouseDelta();

    CameraYaw(camera, -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, false);
    CameraPitch(camera, -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, true, false, false);
}

void drawWalls(Wall walls)
{
    DrawCube(walls.wallPositionTop, 100.0f, 0.0f, 100.0f, LOWDARK);
    DrawCube(walls.wallPositionRight, 100.0f, 100.0f, 1.0f, LOWDARK);
    DrawCube(walls.wallPositionLeft, 100.0f, 100.0f, 1.0f, LOWDARK);
    DrawCube(walls.wallPositionInFront, 1.0f, 100.0f, 100.0f, LOWDARK);
    DrawCube(walls.wallPositionBehind, 0.0f, 100.0f, 100.0f, LOWDARK);
    DrawCube(walls.wallPositionBottom, 100.0f, 0.0f, 100.0f, LOWDARK);
}
