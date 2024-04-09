#include "../include/raylib.h"
#include "../include/rcamera.h"
#include "../include/raymath.h"
// #include "../include/walls.h"
#include "../include/particle.h"
#include <iostream>

using namespace std;
const int screenWidth = 1920;
const int screenHeight = 1080;
Vector2 mousePosition = {0.0f, 0.0f};

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.001f // TODO: it should be independant of framerate

void UpdateCamera(Camera *camera);
void updateParticlesTime(float timePlayed, Particle particles[]);
void drawRectangule();
// void drawWalls(Wall walls);

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Testing particles");
    // Wall walls;

    Particle particles[MAX_PARTICLES];

    int particleCount = initializeParticles(particles);
    float frameTime = GetFrameTime();

    float deltaTime = 0.0f;
    InitAudioDevice();

    Music song = LoadMusicStream("song/song.wav");
    SetMusicVolume(song, 0.1f);
    char timeText[20];
    float progress;
    Camera3D camera = {0};
    camera.position = (Vector3){-15.0f, 0.0f, 0.0f};
    camera.target = (Vector3){1.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 100.0f;

    Camera2D camera2D_ = {0};
    camera2D_.offset = (Vector2){0.0f, 0.0f};
    camera2D_.rotation = 0.0f;
    camera2D_.target = (Vector2){0.0f, 0.0f};
    camera2D_.zoom = 1.0f;

    int rectWidth = 800;
    int rectHeight = 800;
    int rectX = (screenWidth - rectWidth) / 2;
    int rectY = (screenHeight - rectHeight) / 2;

    PlayMusicStream(song);
    SetMousePosition(screenWidth/2,screenHeight/2);

    SetTargetFPS(165);
    DisableCursor();

    while (!WindowShouldClose())
    {
        frameTime = GetFrameTime();
        deltaTime += frameTime;
        mousePosition = GetMousePosition();
        UpdateCamera(&camera);
        UpdateMusicStream(song);

        progress = GetMusicTimePlayed(song);
        updateParticlesTime(progress, particles);
        sprintf(timeText, "TIME: %.2f s", progress);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode2D(camera2D_);
        DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, WHITE);
        EndMode2D();

        BeginMode3D(camera);

        if (deltaTime > 0.5f)
        {
            drawParticles(particles, particleCount);
            UpdateParticlesPosition(particles, particleCount, frameTime);
        }

        // DrawCubeWires({0.0f, 0.0f, 0.0f}, 0.0f, 25.0f, 25.0f, WHITE);
        EndMode3D();

        DrawRectangle(50, 50, 10 * progress, 20, RED);
        DrawText(timeText, 50, 80, 20, WHITE);
        drawRectangule();

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

void updateParticlesTime(float timePlayed, Particle particles[])
{
    if (timePlayed >= 3.7f && timePlayed < 3.8f)
    {
        modifyColorParticles(RED, particles);
        return;
    }

    if (timePlayed >= 4.1f && timePlayed < 4.2f)
    {
        modifyColorParticles(BLUE, particles);
        return;
    }

    if (timePlayed >= 4.6f && timePlayed < 4.7f)
    {
        modifyColorParticles(WHITE, particles);
        return;
    }

    if (timePlayed >= 5.1f && timePlayed < 5.2f)
    {
        modifyColorParticles(GREEN, particles);
        return;
    }

    if (timePlayed >= 5.6f && timePlayed < 5.7f)
    {
        modifyColorParticles(PURPLE, particles);
        return;
    }

    if (timePlayed >= 6.1f && timePlayed < 6.2f)
    {
        modifyColorParticles(WHITE, particles);
        return;
    }

    if (timePlayed >= 6.6f && timePlayed < 6.7f)
    {
        modifyColorParticles(ORANGE, particles);
        return;
    }

    if (timePlayed >= 7.1f && timePlayed < 7.2f)
    {
        modifyColorParticles(LIME, particles);
        return;
    }

    if (timePlayed >= 7.6f && timePlayed < 7.7f)
    {
        modifyColorParticles(PINK, particles);
        return;
    }

    if (timePlayed >= 8.1f && timePlayed < 8.2f)
    {
        modifyColorParticles(GOLD, particles);
        return;
    }

    if (timePlayed >= 8.6f && timePlayed < 8.7f)
    {
        modifyColorParticles(GREEN, particles);
        return;
    }

    if (timePlayed >= 9.1f && timePlayed < 9.2f)
    {
        modifyColorParticles(WHITE, particles);
        return;
    }

    if (timePlayed >= 9.6f && timePlayed < 9.7f)
    {
        modifyColorParticles(GOLD, particles);
        return;
    }

    if (timePlayed >= 10.1f && timePlayed < 10.2f)
    {
        modifyColorParticles(RED, particles);
        return;
    }

    if (timePlayed >= 10.6f && timePlayed < 10.7f)
    {
        modifyColorParticles(PURPLE, particles);
        return;
    }

    if (timePlayed >= 11.1f && timePlayed < 11.2f)
    {
        modifyColorParticles(GREEN, particles);
        return;
    }

    if (timePlayed >= 11.6f && timePlayed < 11.7f)
    {
        modifyColorParticles(YELLOW, particles);
        return;
    }
}

void drawRectangule()
{
    int rectWidth = 80;
    int rectHeight = 80;

    int rectX = mousePosition.x - rectWidth / 2;
    int rectY = mousePosition.y - rectHeight / 2;

    DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, WHITE);
}