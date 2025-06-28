#include "pch.h"

#include "layered_renderer.hxx"

scene::id_type scene::LayeredRenderer::push_layer()
{
    auto layer = vtkSmartPointer<vtkRenderer>::New();

    layer->SetActiveCamera(_base_renderer->GetActiveCamera());
    layer->SetBackgroundAlpha(0);

    _layers.insert_or_assign(_layers_inserter_index, layer);
    layer->SetLayer(_layers_inserter_index);

    ++_layers_inserter_index;

    _window->SetNumberOfLayers(_layers_inserter_index);
    _window->AddRenderer(layer);

    return _layers_inserter_index;
}

scene::id_type scene::LayeredRenderer::pop_layer()
{
    return id_type();
}

scene::LayeredRenderer::SceneIndex scene::LayeredRenderer::add_prop(id_type layer_id, vtkSmartPointer<vtkProp3D>& prop)
{
    return SceneIndex();
}

void scene::LayeredRenderer::remove_prop(id_type layer_id, id_type prop_id)
{
    if(!_layered_props.contains(layer_id)) {
        throw std::runtime_error("Trying to get non-existing layer!");
    }

    auto props_collection = _layered_props[layer_id];

    if(!props_collection.contains(prop_id)) {
        throw std::runtime_error("Trying to get non-existing prop!");
    }

    auto prop = props_collection.at(prop_id);

    auto layer = get_layer(layer_id);

    layer->RemoveViewProp(prop);
    layer->Render();
}

void scene::LayeredRenderer::move_prop(id_type from_layer, id_type to_layer)
{
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
    if(!_layers.contains(id)) {
        throw std::runtime_error("Trying to get a non-existing layer!");
    }
    
    return _layers.at(id);
}

vtkSmartPointer<vtkRenderer> scene::LayeredRenderer::get_base_layer() const
{
    return vtkSmartPointer<vtkRenderer>();
}
