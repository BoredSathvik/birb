#include "Zoom.h"

void Zoom::OnKey(int key, bool pressed)
{
    if (key == 'G')
    {
        if (pressed)
        {
            fov_before = *fov;
            *minFov = 0.0f;
            *fov = 30.0f;
            zoom = true;
        }
        else
        {
            *fov = fov_before;
            *minFov = 30.0f;
            zoom = false;
        }
    }
}

void Zoom::OnMouse(char button, char pressed, short mX, short mY)
{
    if (zoom)
    {
        if (button == 4)
        {
            if (pressed == 120)
            {
                *fov += 5;
            }
            else if (pressed == -120)
            {
                *fov -= 5;
            }
        }
    }
}
