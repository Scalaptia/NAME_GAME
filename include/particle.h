#include "raylib.h"
#include <iostream>

using namespace std;

#define MAX_PARTICLES 200
#define PARTICLE_SPEED_X -200.0f
#define PARTICLE_SPEED_Y 0.0f
#define PARTICLE_SPEED_Z 0.0f

#define PARTICLE_SIZE 1.5f
#define PARTICLE_MAX_SIZE 15.0f

// CHANGE COLOR OF THE PARTICLES HERE.
#define BLUEGRAY \
    CLITERAL(Color) { 116, 160, 195, 255 }
#define BLUEGRAYDARK \
    CLITERAL(Color) { 39, 42, 56, 255 }
#define PURPLELIGHT \
    CLITERAL(Color) { 220, 185, 255, 255 }

Color changeColorParticle();
class Particle
{
public:
    Vector3 position;
    Color color;
    float alpha;
    float size;
    bool active;
    Vector3 particleSpeed;
    float lifeSpan;
    bool growing;

public:
    void updateParticle();
};

void Particle::updateParticle()
{
    this->alpha = 1.0f;
    this->size = PARTICLE_SIZE + (float)GetRandomValue(1, PARTICLE_MAX_SIZE) / 15.0f;
    this->active = false;

    do
    {
        this->position.x = (float)GetRandomValue(-100, 500);
        this->position.y = (float)GetRandomValue(-200, 200);
        this->position.z = (float)GetRandomValue(-300, 300);
    } while (this->position.x >= -50 && this->position.x <= 50 &&
             this->position.y >= -20 && this->position.y <= 20 &&
             this->position.z >= -20 && this->position.z <= 20);

    this->lifeSpan = (float)GetRandomValue(20, 30);
    this->particleSpeed = (Vector3){PARTICLE_SPEED_X, PARTICLE_SPEED_Y, PARTICLE_SPEED_Z};
    this->growing = GetRandomValue(0, 1);
}
// --------------- PROTOTYPE ----------------------------
Particle getNewParticle();
int initializeParticles(Particle particles[]);
void drawParticles(Particle particles[], int particleCount);
void UpdateParticlesPosition(Particle particles[], int particleCount, float frameTime);
bool areColorsEqual(Color color1, Color color2);

// --------------- FUNCTIONS DEVELOPEMENT ----------------------------
Particle getNewParticle()
{
    Particle newParticle;
    newParticle.alpha = 1.0f;
    newParticle.size = 0.0f;
    newParticle.active = false;
    do
    {
        newParticle.position.x = (float)GetRandomValue(-100, 300);
        newParticle.position.y = (float)GetRandomValue(-200, 200);
        newParticle.position.z = (float)GetRandomValue(-300, 300);
    } while (newParticle.position.x >= -50 && newParticle.position.x <= 50 &&
             newParticle.position.y >= -20 && newParticle.position.y <= 20 &&
             newParticle.position.z >= -20 && newParticle.position.z <= 20);

    newParticle.lifeSpan = (float)GetRandomValue(20, 30);
    newParticle.particleSpeed = (Vector3){PARTICLE_SPEED_X, PARTICLE_SPEED_Y, PARTICLE_SPEED_Z};
    newParticle.growing = GetRandomValue(0, 1);
    newParticle.color = changeColorParticle();

    return newParticle;
}

int initializeParticles(Particle particles[])
{
    int particleCount = 0;
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particles[i] = getNewParticle();
        particleCount++;
    }
    return particleCount;
}

void drawParticles(Particle particles[], int particleCount)
{
    for (int i = 0; i < particleCount; i++)
    {
        DrawSphereEx(particles[i].position, particles[i].size, 10, 10, particles[i].color);
    }
}

void UpdateParticlesPosition(Particle particles[], int particleCount, float frameTime)
{

    for (int i = 0; i < particleCount; i++)
    {

        particles[i].position.x += particles[i].particleSpeed.x * frameTime;
        particles[i].position.y += particles[i].particleSpeed.y * frameTime;
        particles[i].position.z += particles[i].particleSpeed.z * frameTime;

        if (particles[i].position.x <= 200)
        {
            if (particles[i].position.y <= 30 && particles[i].position.y >= -30)
            {
                if (particles[i].position.z <= 30 && particles[i].position.z >= -30)
                {
                    particles[i].size = -1.0f;
                    particles[i].growing = false;
                }
            }
        }

        if (particles[i].growing)
        {
            particles[i].size = particles[i].size + frameTime;
        }
        else
        {
            particles[i].size = particles[i].size - frameTime;
        }

        if (particles[i].growing && particles[i].size >= 1.0f)
        {
            particles[i].growing = false;
        }
        else if (!particles[i].growing && particles[i].size <= 0.0f)
        {
            particles[i].updateParticle();
        }
    }
}

Color changeColorParticle()
{
    if (GetRandomValue(0, 1))
    {
        return BLUEGRAY;
    }

    return BLUEGRAYDARK;
}

void modifyColorParticles(Color color, Particle particles[])
{
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        if (!areColorsEqual(particles[i].color, BLUEGRAYDARK))
        { 
            particles[i].color = color;
        }
    }
}

bool areColorsEqual(Color color1, Color color2)
{
    return (color1.a == color2.a) && (color1.r == color2.r) && (color1.g == color2.g) && (color1.b == color2.b);
}