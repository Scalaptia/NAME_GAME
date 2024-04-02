#include "../include/raylib.h"
#include "../include/rcamera.h"
#include "../include/raymath.h"
// #include "../include/walls.h"
#include "../include/particle.h"
#include <iostream>

using namespace std;

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.001f // TODO: it should be independant of framerate

void UpdateCamera(Camera *camera);
// void drawWalls(Wall walls);

int main(void)
{

    const int screenWidth = 1920;
    const int screenHeight = 1080;

    InitWindow(screenWidth, screenHeight, "Testing particles");
    // Wall walls;

    Particle particles[MAX_PARTICLES];

    int particleCount = initializeParticles(particles);
    float frameTime = GetFrameTime();

    float deltaTime = 0.0f;
    InitAudioDevice();

    Music song = LoadMusicStream("song/song.wav");
    SetMusicVolume(song, 0.0010f);
    char timeText[20];

    float progress;
    // walls.wallPositionTop = {0.0f, 50.0f, 0.0f};
    // walls.wallPositionBottom = {0.0f, -50.0f, 0.0f};

    // walls.wallPositionInFront = {50.0f, 0.0f, 0.0f};
    // walls.wallPositionBehind = {-50.0f, 0.0f, 0.0f};

    // walls.wallPositionLeft = {-0.0f, 0.0f, -50.0f};
    // walls.wallPositionRight = {0.0f, 0.0f, 50.0f};

    Camera3D camera = {0};
    camera.position = (Vector3){0.0f, 3.0f, 0.0f};
    camera.target = (Vector3){3.0f, 3.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 120.0f;

    PlayMusicStream(song);

    DisableCursor();

    SetTargetFPS(165);

    while (!WindowShouldClose())
    {
        frameTime = GetFrameTime();
        deltaTime += frameTime;
        UpdateCamera(&camera, CAMERA_FREE);
        UpdateMusicStream(song);
        progress = GetMusicTimePlayed(song);
        BeginDrawing();
        ClearBackground(LOWDARK);
        BeginMode3D(camera);

        if (deltaTime > 0.5f)
        {
            drawParticles(particles, particleCount);
            UpdateParticlesPosition(particles, particleCount, frameTime);
        }

        // printf("X: %f, Y: %f, Z: %f\n", camera.target.x, camera.target.y, camera.target.z);

        // drawWalls(walls);
        DrawCubeWires({0.0f, 3.0f, 0.0f}, 5.0f, 5.0f, 5.0f, WHITE);
        // DrawGrid(100, 5.0f);

        EndMode3D();

        DrawRectangle(50, 50, 10 * progress, 20, RED);
        sprintf(timeText, "TIME: %.2f s", progress);
        DrawText(timeText, 50, 80, 20, WHITE);

        EndDrawing();
    }
    StopMusicStream(song);
    UnloadMusicStream(song);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}

void UpdateCamera(Camera *camera)
{
    Vector2 mousePositionDelta = GetMouseDelta();

    CameraYaw(camera, -mousePositionDelta.x * CAMERA_MOUSE_MOVE_SENSITIVITY, false);
    CameraPitch(camera, -mousePositionDelta.y * CAMERA_MOUSE_MOVE_SENSITIVITY, true, false, false);
}

bool detectarBajos(float *audioData, int numSamples)
{
    float promedio = 0.0f;
    float umbral = 0.1f;
    for (int i = 0; i < numSamples; i++)
    {
        promedio += fabs(audioData[i]);
    }
    promedio /= numSamples;

    if (promedio > umbral)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// void drawWalls(Wall walls)
// {
//     DrawCube(walls.wallPositionTop, 100.0f, 0.0f, 100.0f, LOWDARK);
//     DrawCube(walls.wallPositionRight, 100.0f, 100.0f, 1.0f, LOWDARK);
//     DrawCube(walls.wallPositionLeft, 100.0f, 100.0f, 1.0f, LOWDARK);
//     DrawCube(walls.wallPositionInFront, 1.0f, 100.0f, 100.0f, LOWDARK);
//     DrawCube(walls.wallPositionBehind, 0.0f, 100.0f, 100.0f, LOWDARK);
//     DrawCube(walls.wallPositionBottom, 100.0f, 0.0f, 100.0f, LOWDARK);
// }
