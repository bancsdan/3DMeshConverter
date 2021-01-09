#include <cstdint>
#include <math.h>

#include "utility.hpp"
#include "geometry/vector3d.hpp"

bool Utility::IsLittleEndian()
{
        int16_t i = 1;
        char* p = (char*)&i;
        return p[0] == 1;
}
