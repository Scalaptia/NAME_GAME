#include "raylib.h"

#define MAX_PARTICLES 100
#define PARTICLE_SPEED 0.3

typedef struct _Particle
{
    Vector3 position;
    Color color;
    float alpha;
    float size;
    bool active;
    Vector3 particleSpeed;
    float lifeSpan;
} Particle;

int initializeParticles(Particle particleses[])
{
    int particleCount = 0;
    for (int i = 0; i < MAX_PARTICLES; i++)
    {
        particleses[i].color = (Color){GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255};
        particleses[i].alpha = 1.0f;
        particleses[i].size = (float)GetRandomValue(1, 5) / 20.0f;
        particleses[i].active = false;
        particleses[i].position.x = (float)GetRandomValue(-10, 10);
        particleses[i].position.y = (float)GetRandomValue(-10, 10);
        particleses[i].position.z = (float)GetRandomValue(-10, 10);
        particleses[i].lifeSpan = (float)GetRandomValue(20, 30);
        particleses[i].particleSpeed = (Vector3){(float)GetRandomValue(-1, 1), (float)GetRandomValue(-1, 1), (float)GetRandomValue(-1, 1)};
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

int UpdateParticlesPosition(Particle Particles[], int particleCount)
{
    float frameTime = GetFrameTime();

    for (int i = 0; i < particleCount; i++)
    {
        Particles[i].position.x += Particles[i].particleSpeed.x * frameTime;
        Particles[i].position.y += Particles[i].particleSpeed.y * frameTime;
        Particles[i].position.z += Particles[i].particleSpeed.z * frameTime;
        Particles[i].lifeSpan -= frameTime;

        if (Particles[i].lifeSpan <= 0)
        {
            Particles[i] = Particles[particleCount - 1];
            particleCount--;
        }
        
    }

    return particleCount;
}
