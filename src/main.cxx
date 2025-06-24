#include "pch.h"

#include "composite_renderer.hxx"
#include "vtk_generators.hxx"

static void perf_count(vtkObject* caller, unsigned long, void*, void*) 
{
    vtkRenderer* renderer = static_cast<vtkRenderer*>(caller);

    double frame_time = renderer->GetLastRenderTimeInSeconds();
    double fps = 1.0 / frame_time;

    auto msg = std::format("FPS: {}", fps);

    std::cout << msg << "\n";
}

int main(int argc, char** argv) 
{
    if(argc < 2) {
        std::cout << "not enough run parameters\n";
    }

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

    vtkNew<vtkCallbackCommand> callback;
    callback->SetCallback(perf_count);
    renderer->AddObserver(vtkCommand::EndEvent, callback);

    auto run_parameter = argv[1];
    if(std::strcmp(run_parameter, "-c") == 0) {
        std::cout << "Requested composite rendering\n";

        auto composite_renderer = new scene::VtkCompositeSceneRenderer();

        double x{}, y{}, z{};
        for(auto i = 0; i < 130; ++i) {
            common::Colord color(0.3, 0.8, 0.1);
            common::Vec3d position(x, y, z);
            auto block = generators::make_sphere(position, 4, color, generators::MEDIUM);
            composite_renderer->add_block(block);
            
            x+=10;
            y+=10;
            z+=10;
        }

        composite_renderer->update();

        composite_renderer->set_renderer(renderer);
    } 
    else if(std::strcmp(run_parameter, "-a") == 0) {
        std::cout << "Requested actors rendering\n";

        double x{}, y{}, z{};
        for(auto i = 0; i < 130; ++i) {
            common::Colord color(0.3, 0.8, 0.1);
            common::Vec3d position(x, y, z);
            auto block = generators::make_sphere(position, 4, color, generators::MEDIUM);
            
            vtkNew<vtkPolyDataMapper> mapper;
            mapper->SetInputData(block);

            mapper->Update();

            vtkNew<vtkActor> actor;
            actor->SetMapper(mapper);

            x+=10;
            y+=10;
            z+=10;

            renderer->AddActor(actor);
        }
    }

    renderWindow->Render();
    interactor->Start();

    return 0;
}