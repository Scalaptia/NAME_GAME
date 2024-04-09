#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
// #include "../include/walls.h"
#include "particle.h"
#include <iostream>

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY 0.001f // TODO: it should be independant of framerate

// Mouse Square Gloabal variables
#define SIZE_SQUARE_MOUSE 80
#define AREA_X_MIN 600
#define AREA_Y_MIN 180
#define AREA_X_MAX 1320
#define AREA_Y_MAX 900

// 3D Camera Global Variables Ajustment
#define AJUST_CAMERA 0.015f //This variable ajusts how much/far will move the camera in the 3D world. 

using namespace std;
const int screenWidth = 1920;
const int screenHeight = 1080;
Vector2 mousePosition = {0.0f, 0.0f};
Vector2 prevMouse = {0.0f, 0.0f};
bool isMouseOnPosition = true;

// PROTOTYPE FUNCTIONS
void UpdateCamera(Camera *camera);
void updateParticlesTime(float timePlayed, Particle particles[]);
void drawRectangule();
void verifyMousePosition();
// void drawWalls(Wall walls);

int main(void)
{

    InitWindow(screenWidth, screenHeight, "Testing particles");

    Particle particles[MAX_PARTICLES];

    // Variables to modify Camera Position in 3D particles.
    float deltaZ;
    float deltaY;

    int particleCount = initializeParticles(particles);
    float frameTime;

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

    int rectWidth = 800;
    int rectHeight = 800;
    int rectX = (screenWidth - rectWidth) / 2;
    int rectY = (screenHeight - rectHeight) / 2;

    PlayMusicStream(song);
    SetMousePosition(screenWidth / 2, screenHeight / 2);

    SetTargetFPS(165);
    DisableCursor();
    mousePosition = GetMousePosition();

    while (!WindowShouldClose())
    {
        // Update variables
        frameTime = GetFrameTime();
        deltaTime += frameTime;
        prevMouse = mousePosition;
        mousePosition = GetMousePosition();
        verifyMousePosition();

        // Ajusting 3D camera position using mouse position
        deltaZ = mousePosition.x - prevMouse.x;
        deltaY = mousePosition.y - prevMouse.y;

        camera.position.z -= deltaZ * AJUST_CAMERA;
        camera.position.y += deltaY * AJUST_CAMERA;

        // Update functions
        UpdateCamera(&camera);
        UpdateMusicStream(song);
        progress = GetMusicTimePlayed(song);
        updateParticlesTime(progress, particles);
        sprintf(timeText, "TIME: %.2f s", progress);

        // ********** DRAWING ************
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw particles
        BeginMode3D(camera);

        if (deltaTime > 0.5f)
        {
            drawParticles(particles, particleCount);
            UpdateParticlesPosition(particles, particleCount, frameTime);
        }
        EndMode3D();

        // Draw Big Square
        DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, WHITE);

        // Draw time
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
    if (isMouseOnPosition)
    {
        int rectWidth = SIZE_SQUARE_MOUSE;
        int rectHeight = SIZE_SQUARE_MOUSE;

        int rectX = mousePosition.x - rectWidth / 2;
        int rectY = mousePosition.y - rectHeight / 2;

        DrawRectangleLines(rectX, rectY, rectWidth, rectHeight, WHITE);
    }
}

void verifyMousePosition()
{
    if (mousePosition.x < AREA_X_MIN)
    {
        mousePosition.x = AREA_X_MIN;
    }
    else if (mousePosition.x > AREA_X_MAX)
    {
        mousePosition.x = AREA_X_MAX;
    }

    if (mousePosition.y < AREA_Y_MIN)
    {
        mousePosition.y = AREA_Y_MIN;
    }
    else if (mousePosition.y > AREA_Y_MAX)
    {
        mousePosition.y = AREA_Y_MAX;
    }

    SetMousePosition(mousePosition.x, mousePosition.y);
}
