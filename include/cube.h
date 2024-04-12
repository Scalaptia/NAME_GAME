#include "raylib.h"

class Cube
{
protected:
    Vector3 position;
    Vector3 size;
    Color color;
    float speed;

public:
    Cube(Vector3 position, Vector3 size, Color color, float speed)
    {
        this->position = position;
        this->size = size;
        this->color = color;
        this->speed = speed;
    }

    void update()
    {
        position.x -= speed;
        if (position.x < -12)
        {
            position.x = 0;
        }
    }

    void draw()
    {
        DrawCube(position, size.x, size.y, size.z, color);
    }

    void drawWireframe()
    {
        DrawCubeWires(position, size.x, size.y, size.z, color);
    }
};