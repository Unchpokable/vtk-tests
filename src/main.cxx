#include "pch.h"

#include "composite_renderer.hxx"
#include "vtk_generators.hxx"

int main(int argc, char** argv) 
{
    auto composite_renderer = new scene::VtkCompositeSceneRenderer();

    double x{}, y{}, z{};
    for(auto i = 0; i < 1000; ++i) {
        common::Colord color(0.3, 0.8, 0.1);
        common::Vec3d position(x, y, z);
        auto block = generators::make_sphere(position, 4, color, generators::MEDIUM);
        composite_renderer->add_block(block);
        
        x+=10;
        y+=10;
        z+=10;
    }

    composite_renderer->update();

    vtkNew<vtkRenderer> renderer;
    renderer->SetBackground(0.1, 0.2, 0.4);

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(800, 600);
    renderWindow->SetWindowName("VTK Minimal Example");

    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor->SetInteractorStyle(style);

    composite_renderer->set_renderer(renderer);

    renderWindow->Render();
    interactor->Start();

    return 0;
}