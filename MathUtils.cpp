#include "MathUtils.h"
#include "Engine.h"

#include <time.h>

static bool rand_seeded = false;

static void seed_rng()
{
    srand(static_cast<unsigned>(time(NULL)));
    rand_seeded = true;
}

float Util::Degrees(float rads)
{
    return (float)(360.f * (double)rads / (2.0 * M_PI));
}

float Util::Radians(float degs)
{
    return (float)((2.0 * M_PI) * degs / 360.f);
}

float Util::Random(float min, float max)
{
    if (!rand_seeded) seed_rng();
    float range = max - min;
    float pct = (float)((double)rand() / (double)RAND_MAX);
    return range * pct + min;
}
