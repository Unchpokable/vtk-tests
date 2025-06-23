#ifndef UNC_COMMON_H
#define UNC_COMMON_H

#define align(type) alignas(sizeof(type))

namespace common 
{

struct align(float) Vec3f 
{
    float x, y, z;
};

struct align(float) Colorf 
{
    float r, g, b;
};

union Position {
    Vec3f xyz;
    float raw[3];
};

union Color {
    Colorf rgb;
    float raw[3];
};

}


#endif