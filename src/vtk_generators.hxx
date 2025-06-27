#ifndef UNC_VTK_GENERATORS_H
#define UNC_VTK_GENERATORS_H

#include "common_types.hxx"

namespace generators
{
constexpr double resolution_base = 4.0;

enum Resolution : int
{
    DOGSHIT = 1,
    LOW = 2,
    MEDIUM = 3,
    HIGH = 4,
    PLEASEHELP = 5
};
} // namespace generators

namespace generators
{
vtkSmartPointer<vtkPolyData> make_sphere(const common::Vec3d& pos, double size, Resolution resolution);
vtkSmartPointer<vtkPolyData> make_sphere(
    const common::Vec3d& pos, double size, const common::Colord& color, Resolution resolution);
vtkSmartPointer<vtkPolyData> make_cylinder(
    const common::Vec3d& pos, double radius, double length, const common::Colord& color, Resolution resolution);
} // namespace generators

#endif // VTK generators