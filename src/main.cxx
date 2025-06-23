#include "pch.h"

int main(int argc, char** argv) 
{
    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->SetRadius(1.0);
    sphereSource->SetThetaResolution(30);
    sphereSource->SetPhiResolution(30);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(sphereSource->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(0.1, 0.2, 0.4);

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    renderWindow->SetWindowName("VTK Minimal Example");

    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor->SetInteractorStyle(style);

    renderWindow->Render();
    interactor->Start();

    return 0;
}