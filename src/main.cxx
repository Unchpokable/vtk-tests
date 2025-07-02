#include "pch.hxx"

#include "composite_scene_object.hxx"
#include "layered_renderer.hxx"
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

    vtkNew<vtkRenderWindow> renderWindow;
    renderWindow->SetSize(800, 600);
    renderWindow->SetWindowName("Layered Multiblock composite renderer test");

    vtkNew<vtkRenderWindowInteractor> interactor;
    interactor->SetRenderWindow(renderWindow);

    vtkNew<vtkInteractorStyleTrackballCamera> style;
    interactor->SetInteractorStyle(style);

    auto layered_renderer = std::make_unique<scene::LayeredRenderer>(renderWindow);
    auto layer_id = layered_renderer->push_layer();
    auto overlay_id = layered_renderer->push_layer();

    layered_renderer->set_backgroud(common::Colord(0.3, 0.3, 0.3));

    auto run_parameter = argv[1];
    int spheres_count;
    if(argc >= 3) {
        std::sscanf(argv[2], "%i", &spheres_count);
    }
    else {
        spheres_count = 1;
    }

    if(std::strcmp(run_parameter, "-c") == 0) {
        std::cout << "Requested composite rendering\n";

        auto composite_object = std::make_unique<scene::CompositeSceneObject>(0);

        double x {}, y {}, z {};
        for(auto i = 0; i < spheres_count; ++i) {
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
            auto block_id = composite_object->add_block(block);
            composite_object->set_color(block_id, color);

            x += 10;
            y += 10;
            z += 10;
        }

        composite_object->update();

        composite_object->set_renderer(layered_renderer->get_layer(layer_id));
    }
    else if(std::strcmp(run_parameter, "-a") == 0) {
        std::cout << "Requested actors rendering\n";

        double x {}, y {}, z {};
        for(auto i = 0; i < spheres_count; ++i) {
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

            layered_renderer->add_prop(layer_id, actor);
        }
    }

    auto overlay_composite = std::make_unique<scene::CompositeSceneObject>(1);

    auto overlaying_sphere =
        generators::make_sphere(common::Vec3d(0, 0, 0), 3, common::Colord(1.0, 0.0, 0.0), generators::HIGH);

    overlay_composite->add_block(overlaying_sphere);
    overlay_composite->set_renderer(layered_renderer->get_layer(overlay_id));
    overlay_composite->update();

    layered_renderer->fix_clip();

    renderWindow->Render();
    interactor->Start();

    return 0;
}