#include "pch.h"

#include "vtk_generators.hxx"
#include "utils.hxx"

vtkSmartPointer<vtkPolyData> generators::make_sphere(const common::Vec3d& pos, double size, Resolution resolution)
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

vtkSmartPointer<vtkPolyData> generators::make_sphere(const common::Vec3d& pos, double size, const common::Colord& color,
    Resolution resolution)
{
    auto result = make_sphere(pos, size, resolution);
    
    vtkNew<vtkUnsignedCharArray> colors;
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");
    
    auto color_array = utils::make_uchar_color(color);
    
    vtkIdType cells_count = result->GetNumberOfCells();
    colors->SetNumberOfTuples(cells_count);
    for (vtkIdType i = 0; i < cells_count; ++i) {
        colors->SetTuple3(i, color_array[0], color_array[1], color_array[2]);
    }
    
    result->GetCellData()->SetScalars(colors);
    return result;
}

vtkSmartPointer<vtkPolyData> generators::make_cylinder(const common::Vec3d& pos, double radius, double length, 
    const common::Colord& color, Resolution resolution)
{
    return vtkSmartPointer<vtkPolyData>();
}
