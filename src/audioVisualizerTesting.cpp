#include "raylib.h"
#include <iostream>

#define N (1<<12)
#define TARGET_FREQ_SIZE 10
#define TWO_PI 6.28318530717959

int SCREEN_WIDTH = 1920;
int SCREEN_HEIGHT = 1080;



typedef struct
{
    /* data */
    float input_raw_Data[N];
    float input_data_with_windowing_function[N];
    float output_raw_Data[N];
    float frequency_sqr_mag[N/2];
    float smooth_spectrum[TARGET_FREQ_SIZE-1];
} Data;

Data data;


void main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Testing audio visualizer");
    InitAudioDevice();
    Music song = "song/song.wav";

    while (!WindowShouldClose())
    {
        
    }
    CloseWindow();
}

void VisualizeSpectrum(float spectrum_scaling_factor)
{
    int h = SCREEN_HEIGHT - 32;
    for (size_t i = 0; i < TARGET_FREQ_SIZE-1; i++) {
        /* code */
        DrawRectangleLines(184 + (i * 16), h - (spectrum_scaling_factor*data.smooth_spectrum[i]), 15, (spectrum_scaling_factor*data.smooth_spectrum[i]), SPECTRUM_COLOR);
    }
}
