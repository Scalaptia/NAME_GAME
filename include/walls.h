#include "raylib.h"

typedef struct _Wall 
{
    Vector3 wallPositionTop;
    Vector3 wallPositionBottom;
    Vector3 wallPositionRight;
    Vector3 wallPositionLeft;
    Vector3 wallPositionInFront;
    Vector3 wallPositionBehind;
} Wall;