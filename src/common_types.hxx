#ifndef UNC_COMMON_H
#define UNC_COMMON_H

namespace common 
{

struct Vec3d 
{
    Vec3d(double x, double y, double z);

    double& x() { return data[0]; }
    double& y() { return data[1]; }
    double& z() { return data[2]; }
    
    const double& x() const { return data[0]; }
    const double& y() const { return data[1]; }
    const double& z() const { return data[2]; }
    
    constexpr operator double*() { return data; }
    constexpr operator const double*() const { return data; }

private:
    double data[3];
};

struct Colord 
{
    Colord(double r, double g, double b);

    double& r() { return data[0]; }
    double& g() { return data[1]; }
    double& b() { return data[2]; }
    
    const double& r() const { return data[0]; }
    const double& g() const { return data[1]; }
    const double& b() const { return data[2]; }
    
    constexpr operator double*() { return data; }
    constexpr operator const double*() const { return data; }
    
private:
    double data[3];
};

}

#endif