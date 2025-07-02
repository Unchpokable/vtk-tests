#include "pch.hxx"

#include "layered_renderer.hxx"

#include "tassert.hxx"

scene::LayeredRenderer::LayeredRenderer(vtkRenderWindow* render_window)
    : _window(render_window), _layers_count(0), _layers_inserter_index(0)
{
    _base_renderer = vtkSmartPointer<vtkRenderer>::New();
    _base_renderer->SetLayer(0);

    _window->AddRenderer(_base_renderer);
    _window->SetNumberOfLayers(1);
}

scene::id_type scene::LayeredRenderer::push_layer()
{
    auto layer = vtkSmartPointer<vtkRenderer>::New();

    layer->SetActiveCamera(_base_renderer->GetActiveCamera());
    layer->SetBackgroundAlpha(0);

    _layers.insert_or_assign(_layers_inserter_index, layer);
    ++_layers_inserter_index;

    layer->SetLayer(_layers_inserter_index);

    _window->SetNumberOfLayers(_layers_inserter_index + 1);
    _window->AddRenderer(layer);

    ++_layers_count;

    return _layers_inserter_index - 1;
}

scene::id_type scene::LayeredRenderer::pop_layer()
{
    auto layer = _layers.at(_layers_inserter_index - 1);
    _layers.erase(_layers_inserter_index);
    --_layers_inserter_index;

    _window->SetNumberOfLayers(_layers_inserter_index);
    _window->RemoveRenderer(layer);

    --_layers_count;

    return _layers_inserter_index;
}

scene::LayeredRenderer::SceneIndex scene::LayeredRenderer::add_prop(
    id_type layer_id, const vtkSmartPointer<vtkProp3D>& prop)
{
    auto layer = get_layer(layer_id);
    layer->AddViewProp(prop);

    _layered_props[layer_id].insert_or_assign(_prop_inserter_indexes[layer_id], prop);

    SceneIndex index;
    index.layer_id = layer_id;
    index.prop_id = _prop_inserter_indexes[layer_id];

    ++_prop_inserter_indexes[layer_id];

    return index;
}

void scene::LayeredRenderer::remove_prop(id_type layer_id, id_type prop_id)
{
    auto prop = get_prop(layer_id, prop_id);
    auto layer = get_layer(layer_id);

    _layered_props[layer_id].erase(prop_id);
    --_prop_inserter_indexes[layer_id];

    layer->RemoveViewProp(prop);
    layer->Render();
}

void scene::LayeredRenderer::move_prop(id_type prop_id, id_type from_layer, id_type to_layer)
{
    auto prop = get_prop(from_layer, prop_id);

    remove_prop(from_layer, prop_id);
    add_prop(to_layer, prop);
}

vtkProp3D* scene::LayeredRenderer::get_prop(id_type layer_id, id_type prop_id)
{
    assert::cond_fmt(has_layer(layer_id), "Trying to get unexisting layer");

    auto props = _layered_props.at(layer_id);

    assert::cond_fmt(has_prop(layer_id, prop_id), "Trying to get unexisting prop");

    return props.at(prop_id);
}

vtkProp3D* scene::LayeredRenderer::take_prop(id_type layer_id, id_type prop_id)
{
    auto prop = get_prop(layer_id, prop_id);
    auto layer = get_layer(layer_id);

    _layered_props[layer_id].erase(prop_id);
    --_prop_inserter_indexes[layer_id];

    layer->RemoveViewProp(prop);

    return prop;
}

void scene::LayeredRenderer::reset_clipping_range()
{
    for(auto renderer : _layers | std::views::values) {
        renderer->ResetCameraClippingRange();
    }
}

scene::id_type scene::LayeredRenderer::get_layers_count() const
{
    return _layers.size();
}

vtkSmartPointer<vtkRenderer> scene::LayeredRenderer::get_layer(id_type id) const
{
    assert::cond_fmt(has_layer(id), "Trying to get a non-existing layer!");

    return _layers.at(id);
}

vtkSmartPointer<vtkRenderer> scene::LayeredRenderer::get_base_layer() const
{
    return _base_renderer;
}

void scene::LayeredRenderer::update() const
{
    _window->Render();
}

void scene::LayeredRenderer::fix_clip() const
{
    _base_renderer->ResetCameraClippingRange();

    for(auto& layer : _layers | std::views::values) {
        layer->ResetCameraClippingRange();
    }
}

void scene::LayeredRenderer::reset_camera() const
{
    _base_renderer->ResetCamera();

    for(auto& layer : _layers | std::views::values) {
        layer->ResetCamera();
    }
}

void scene::LayeredRenderer::set_backgroud(common::Colord color)
{
    _base_renderer->SetBackground(color);
}

void scene::LayeredRenderer::set_backgroud(common::Colord color1, common::Colord color2)
{
    set_backgroud(color1);
    _base_renderer->SetBackground2(color2);
}

void scene::LayeredRenderer::set_mode(ProjectionMode mode)
{
    switch(mode) {
        case Parallel:
            parallel_projection();
        case Perpective:
            perpective_projection();
    }
}

void scene::LayeredRenderer::parallel_projection()
{
    _base_renderer->GetActiveCamera()->ParallelProjectionOn();

    for(auto& layer : _layers | std::views::values) {
        layer->GetActiveCamera()->ParallelProjectionOn();
    }
}

void scene::LayeredRenderer::perpective_projection()
{

    _base_renderer->GetActiveCamera()->ParallelProjectionOff();

    for(auto& layer : _layers | std::views::values) {
        layer->GetActiveCamera()->ParallelProjectionOff();
    }
}

bool scene::LayeredRenderer::has_layer(id_type layer_id) const
{
    return _layers.contains(layer_id);
}

bool scene::LayeredRenderer::has_prop(id_type layer_id, id_type prop_id) const
{
    if(!has_layer(layer_id)) {
        return false;
    }
    auto it = _layered_props.find(layer_id);
    if(it == _layered_props.end()) {
        return false;
    }
    return it->second.contains(prop_id);
}
