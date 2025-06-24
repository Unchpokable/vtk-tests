#include "pch.h"

#include "vtk_generators.hxx"
#include "utils.hxx"

vtkSmartPointer<vtkPolyData> generators::make_sphere(common::Vec3d& pos, double size, common::Colord& color, 
    Resolution resolution)
{
    auto res = utils::cpow(generators::resolution_base, static_cast<int>(resolution));

    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->SetPhiResolution(res);
    sphereSource->SetThetaResolution(res);
    sphereSource->SetRadius(size);
    sphereSource->Update();

    vtkNew<vtkTransformPolyDataFilter> polyDataFilter;
    vtkNew<vtkTransform> transform;
    transform->Translate(pos);

    polyDataFilter->SetTransform(transform);
    polyDataFilter->SetInputData(sphereSource->GetOutput());
    polyDataFilter->Update();

    auto result = vtkSmartPointer<vtkPolyData>::New();
    result->DeepCopy(polyDataFilter->GetOutput());
    return result;
}

vtkSmartPointer<vtkPolyData> generators::make_cylinder(common::Vec3d& pos, double radius, double length, 
    common::Colord& color, Resolution resolution)
{
    return vtkSmartPointer<vtkPolyData>();
}
