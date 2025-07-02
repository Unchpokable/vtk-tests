#ifndef VTKCOMPOSITE_PCH_H
#define VTKCOMPOSITE_PCH_H

// include stl
#include <array>
#include <concepts>
#include <format>
#include <iostream>
#include <map>
#include <ranges>
#include <type_traits>
#include <unordered_map>
#include <vector>

// include vtk
#include <vtk/vtkCellData.h>
#include <vtk/vtkCellPicker.h>
#include <vtk/vtkInteractorStyleTrackballCamera.h>
#include <vtk/vtkRenderWindow.h>
#include <vtk/vtkRenderWindowInteractor.h>
#include <vtk/vtkRenderer.h>
#include <vtk/vtkSmartPointer.h>
#include <vtk/vtkTransform.h>
#include <vtk/vtkTransformPolyDataFilter.h>

#include <vtk/vtkActor.h>
#include <vtk/vtkCallbackCommand.h>
#include <vtk/vtkCompositeDataDisplayAttributes.h>
#include <vtk/vtkCompositePolyDataMapper.h>
#include <vtk/vtkIntArray.h>
#include <vtk/vtkMultiBlockDataSet.h>
#include <vtk/vtkNew.h>
#include <vtk/vtkPartitionedDataSet.h>
#include <vtk/vtkPolyData.h>
#include <vtk/vtkPolyDataMapper.h>
#include <vtk/vtkSphereSource.h>

#include <vtk/vtkCylinder.h>
#include <vtk/vtkSphere.h>

#endif // vtk-composite-tests precompiled header