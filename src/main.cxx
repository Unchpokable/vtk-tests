#include "pch.hxx"

#include "composite_scene_object.hxx"
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
        return -1;
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

        auto composite_renderer = new scene::CompositeSceneObject(0);

        double x {}, y {}, z {};
        for(auto i = 0; i < 5120; ++i) {
            // Claude codes lmao
            // Generate rainbow gradient: hue varies from 0 to 360 degrees
            float hue = (float(i) / 129.0f) * 360.0f;
            float saturation = 1.0f;
            float value = 1.0f;

            // Convert HSV to RGB
            float c = value * saturation;
            float x_hsv = c * (1.0f - std::abs(std::fmod(hue / 60.0f, 2.0f) - 1.0f));
            float m = value - c;

            float r, g, b;
            if(hue < 60.0f) {
                r = c;
                g = x_hsv;
                b = 0.0f;
            }
            else if(hue < 120.0f) {
                r = x_hsv;
                g = c;
                b = 0.0f;
            }
            else if(hue < 180.0f) {
                r = 0.0f;
                g = c;
                b = x_hsv;
            }
            else if(hue < 240.0f) {
                r = 0.0f;
                g = x_hsv;
                b = c;
            }
            else if(hue < 300.0f) {
                r = x_hsv;
                g = 0.0f;
                b = c;
            }
            else {
                r = c;
                g = 0.0f;
                b = x_hsv;
            }

            common::Colord color(r + m, g + m, b + m);
            common::Vec3d position(x, y, z);
            auto block = generators::make_sphere(position, 4, generators::LOW);
            auto block_id = composite_renderer->add_block(block);
            composite_renderer->set_color(block_id, color);

            x += 10;
            y += 10;
            z += 10;
        }

        composite_renderer->update();

        composite_renderer->set_renderer(renderer);
    }
    else if(std::strcmp(run_parameter, "-a") == 0) {
        std::cout << "Requested actors rendering\n";

        double x {}, y {}, z {};
        for(auto i = 0; i < 5120; ++i) {
            common::Colord color(0.3, 0.8, 0.1);
            common::Vec3d position(x, y, z);
            auto block = generators::make_sphere(position, 4, color, generators::MEDIUM);

            vtkNew<vtkPolyDataMapper> mapper;
            mapper->SetInputData(block);

            mapper->Update();
            mapper->StaticOn();

            vtkNew<vtkActor> actor;
            actor->SetMapper(mapper);

            x += 10;
            y += 10;
            z += 10;

            renderer->AddActor(actor);
        }
    }

    renderWindow->Render();
    interactor->Start();

    return 0;
}