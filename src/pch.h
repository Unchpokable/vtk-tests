#ifndef VTKCOMPOSITE_PCH_H
#define VTKCOMPOSITE_PCH_H

// include stl
#include <vector>
#include <map>
#include <unordered_map>
#include <type_traits>
#include <concepts>
#include <ranges>
#include <array>

// include vtk
#include <vtk/vtkSmartPointer.h>
#include <vtk/vtkRenderWindow.h>
#include <vtk/vtkRenderer.h>
#include <vtk/vtkRenderWindowInteractor.h>
#include <vtk/vtkInteractorStyleTrackballCamera.h>
#include <vtk/vtkTransformPolyDataFilter.h>
#include <vtk/vtkTransform.h>

#include <vtk/vtkActor.h>
#include <vtk/vtkCompositePolyDataMapper.h>
#include <vtk/vtkMultiBlockDataSet.h>
#include <vtk/vtkPartitionedDataSet.h>
#include <vtk/vtkPolyData.h>
#include <vtk/vtkPolyDataMapper.h>
#include <vtk/vtkSphereSource.h>
#include <vtk/vtkNew.h>

#include <vtk/vtkSphere.h>
#include <vtk/vtkCylinder.h>

#endif // vtk-composite-tests precompiled header