#include "pch.h"

#include "vtk_generators.hxx"
#include "utils.hxx"

vtkSmartPointer<vtkPolyData> generators::make_sphere(const common::Vec3d& pos, double size, const common::Colord& color, 
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
    
    // Add colors by cells using vtkUnsignedCharArray with RGB channels
    vtkNew<vtkUnsignedCharArray> colors;
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");
    
    // Convert double color to unsigned char array
    auto colorArray = utils::make_uchar_color(color);
    
    // Set the same color for all cells
    vtkIdType numberOfCells = result->GetNumberOfCells();
    colors->SetNumberOfTuples(numberOfCells);
    for (vtkIdType i = 0; i < numberOfCells; ++i) {
        colors->SetTuple3(i, colorArray[0], colorArray[1], colorArray[2]);
    }
    
    result->GetCellData()->SetScalars(colors);
    return result;
}

vtkSmartPointer<vtkPolyData> generators::make_cylinder(const common::Vec3d& pos, double radius, double length, 
    const common::Colord& color, Resolution resolution)
{
    return vtkSmartPointer<vtkPolyData>();
}
