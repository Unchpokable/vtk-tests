#include "pch.hxx"

#include "common_types.hxx"

common::Vec3d::Vec3d(double x, double y, double z)
{
    data[0] = x;
    data[1] = y;
    data[2] = z;
}

common::Colord::Colord(double r, double g, double b)
{
    data[0] = r;
    data[1] = g;
    data[2] = b;
}
