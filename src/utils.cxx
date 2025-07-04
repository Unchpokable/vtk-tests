#include "pch.hxx"

#include "utils.hxx"

std::string utils::print_boundings(const vtkBoundingBox& box)
{
    double bounds[6]; // xmin, xmax, ymin, ymax, zmin, zmax;
    box.GetBounds(bounds);

    return std::format("Box :: MIN [{}, {}, {}] MAX [{} {} {}]", bounds[0], bounds[2], bounds[4], bounds[1], bounds[3], bounds[5]);
}
