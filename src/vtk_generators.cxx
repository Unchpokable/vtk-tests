#include "pch.h"

#include "vtk_generators.hxx"

vtkSmartPointer<vtkPolyData> generators::make_sphere(common::Position &pos, float size, common::Color &color, 
    Resolution resolution)
{
    return vtkSmartPointer<vtkPolyData>();
}

vtkSmartPointer<vtkPolyData> generators::make_cylinder(common::Position &pos, float radius, float length, 
    common::Color &color, Resolution resolution)
{
    return vtkSmartPointer<vtkPolyData>();
}
