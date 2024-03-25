#include "raylib.h"
#include <iostream>

using namespace std;

#define MAX_PARTICLES 120
#define PARTICLE_SPEED 1.0f

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
    this->color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
    this->alpha = 1.0f;
    this->size = (float)GetRandomValue(1, 10) / 15.0f;
    this->active = false;

    do
    {
        this->position.x = (float)GetRandomValue(-50, 50);
        this->position.y = (float)GetRandomValue(-50, 50);
        this->position.z = (float)GetRandomValue(-50, 50);
    } while (this->position.x >= -10 && this->position.x <= 10 &&
             this->position.y >= -10 && this->position.y <= 10 &&
             this->position.z >= -10 && this->position.z <= 10);

    this->lifeSpan = (float)GetRandomValue(20, 30);
    this->particleSpeed = (Vector3){(float)GetRandomValue(-1, 1), (float)GetRandomValue(-1, 1), (float)GetRandomValue(-1, 1)};
    this->growing = GetRandomValue(0, 1);
}
// --------------- PROTOTYPE ----------------------------
Particle getNewParticle();
int initializeParticles(Particle particleses[]);
void drawParticles(Particle particlses[], int particleCount);
void UpdateParticlesPosition(Particle Particles[], int particleCount, float frameTime);

// --------------- FUNCTIONS DEVELOPEMENT ----------------------------
Particle getNewParticle()
{
    Particle newParticle;
    newParticle.color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
    newParticle.alpha = 1.0f;
    newParticle.size = (float)GetRandomValue(1, 10) / 15.0f;
    newParticle.active = false;
    do
    {
        newParticle.position.x = (float)GetRandomValue(-50, 50);
        newParticle.position.y = (float)GetRandomValue(-50, 50);
        newParticle.position.z = (float)GetRandomValue(-50, 50);
    } while (newParticle.position.x >= -10 && newParticle.position.x <= 10 &&
             newParticle.position.y >= -10 && newParticle.position.y <= 10 &&
             newParticle.position.z >= -10 && newParticle.position.z <= 10);

    newParticle.lifeSpan = (float)GetRandomValue(20, 30);
    newParticle.particleSpeed = (Vector3){(float)GetRandomValue(-1, 1), (float)GetRandomValue(-1, 1), (float)GetRandomValue(-1, 1)};
    newParticle.growing = GetRandomValue(0, 1);
    ;
    return newParticle;
}

int initializeParticles(Particle particleses[])
{
    int particleCount = 0;
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particleses[i] = getNewParticle();
        particleCount++;
    }
    return particleCount;
}

void drawParticles(Particle particlses[], int particleCount)
{
    for (int i = 0; i < particleCount; i++)
    {
        DrawSphereEx(particlses[i].position, particlses[i].size, 10, 10, particlses[i].color);
    }
}

void UpdateParticlesPosition(Particle Particles[], int particleCount, float frameTime)
{

    for (int i = 0; i < particleCount; i++)
    {

        Particles[i].position.x += Particles[i].particleSpeed.x * frameTime;
        Particles[i].position.y += Particles[i].particleSpeed.y * frameTime;
        Particles[i].position.z += Particles[i].particleSpeed.z * frameTime;

        if (Particles[i].growing)
        {
            Particles[i].size = Particles[i].size + frameTime / 3;
        }
        else
        {
            Particles[i].size = Particles[i].size - frameTime / 3;
        }

        if (Particles[i].growing && Particles[i].size >= 1.0f)
        {
            Particles[i].growing = false;
        }
        else if (!Particles[i].growing && Particles[i].size <= 0.0f)
        {
            Particles[i].updateParticle();
        }
    }
}
