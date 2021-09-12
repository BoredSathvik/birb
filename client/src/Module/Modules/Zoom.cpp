#include "Zoom.h"

void Zoom::OnKey(int key, bool pressed)
{
    if (key == 'G')
    {
        if (pressed)
        {
            if (Utils::clientInstance->minecraftGame->canUseKeys)
            {
                fov_before = *fov;
                sen_before = *sen;

                *sen = 0.36;
                *fov = 30.0f;
                *minFov = 0.0f;
                zoom = true;
            }
        }
        else
        {
            *fov = fov_before;
            *minFov = 30.0f;
            *sen = sen_before;
            zoom = false;
        }
    }
}

bool Zoom::OnMouse(char button, char pressed, short mX, short mY)
{
    if (zoom)
    {
        if (button == 4)
        {
            if (pressed == 120)
            {
                if (*fov < 110)
                {
                    *fov += 5;
                    *sen += 0.030;
                }
            }
            else if (pressed == -120)
            {
                if (*fov > 0)
                {
                    *fov -= 5;
                    *sen -= 0.030;
                }
            }
            return true;
        }
    }
    return false;
}
