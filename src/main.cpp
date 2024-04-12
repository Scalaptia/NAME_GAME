#include "raylib.h"
#include "rcamera.h"
#include "raymath.h"
#include "cube.h"
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
#define AJUST_CAMERA 0.015f // This variable ajusts how much/far will move the camera in the 3D world.

using namespace std;
const int screenWidth = 1920;
const int screenHeight = 1080;
Vector2 mousePosition = {0.0f, 0.0f};
Vector2 prevMouse = {0.0f, 0.0f};
bool isMouseOnPosition = true;

float musicBeat[] = {3.7, 4.1, 4.6, 5.1, 5.6, 6.1, 6.6, 7.1, 7.6, 8.1, 8.6, 9.1, 9.6, 10.1, 10.6, 11.1, 11.6, 1500.0};
Color musicBeatColorParticles[] = {RED, BLUE, WHITE, GREEN, PURPLE, WHITE, ORANGE, LIME, PINK, GOLD, GREEN, WHITE, GOLD, RED, PURPLE, GREEN, YELLOW, YELLOW};
int beatPosition = 0;

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
    char timeText[20];
    float progress;

    InitAudioDevice();

    Music song = LoadMusicStream("song/song.wav");
    SetMusicVolume(song, 0.4f);

    Camera3D camera = {0};
    camera.position = (Vector3){-15.0f, 0.0f, 0.0f};
    camera.target = (Vector3){1.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 120.0f;

    int rectWidth = 800;
    int rectHeight = 800;
    int rectX = (screenWidth - rectWidth) / 2;
    int rectY = (screenHeight - rectHeight) / 2;

    // Create cubes in the middle of the screen
    Cube cube1 = Cube(Vector3{-10.0f, 0.0f, 0.0f}, Vector3{1.0f, 1.0f, 1.0f}, RED, 0.1f);
    Cube cube2 = Cube(Vector3{-5.0f, 0.0f, 0.0f}, Vector3{1.0f, 1.0f, 1.0f}, BLUE, 0.1f);
    Cube cube3 = Cube(Vector3{0.0f, 0.0f, 0.0f}, Vector3{1.0f, 1.0f, 1.0f}, GREEN, 0.1f);

    PlayMusicStream(song);
    SetMousePosition(screenWidth / 2, screenHeight / 2);

    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    DisableCursor();
    mousePosition = GetMousePosition();

    while (!WindowShouldClose())
    {
        // Update variables
        frameTime = GetFrameTime();

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
        sprintf(timeText, "TIME: %.2f s", progress);
        updateParticlesTime(progress, particles);

        // Update cubes
        cube1.update();
        cube2.update();
        cube3.update();

        // ********** DRAWING ************
        BeginDrawing();
        ClearBackground(BLACK);

        // Draw particles
        BeginMode3D(camera);

        drawParticles(particles, particleCount);
        UpdateParticlesPosition(particles, particleCount, frameTime);

        // Draw cubes
        cube1.draw();
        cube2.draw();
        cube3.draw();

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
    if (musicBeat[beatPosition] < timePlayed)
    {
        modifyColorParticles(musicBeatColorParticles[beatPosition], particles);
        beatPosition++;
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
