#ifndef UNC_VTK_GENERATORS_H
#define UNC_VTK_GENERATORS_H

#include "common_types.hxx"

namespace generators
{
    enum Resolution 
    {
        DOGSHIT = 1,
        LOW = 2,
        MEDIUM = 4,
        HIGH = 8,
        PLEASEHELP = 16
    };
}

namespace generators 
{
vtkSmartPointer<vtkPolyData> make_sphere(common::Position &pos, float size, common::Color &color, Resolution resolution);
vtkSmartPointer<vtkPolyData> make_cylinder(common::Position &pos, float radius, float length, common::Color &color, Resolution resolution);
}

#endif // VTK generators