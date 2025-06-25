#include "pch.h"

#include "composite_renderer.hxx"

scene::VtkCompositeSceneRenderer::VtkCompositeSceneRenderer()
{
    _data_set = vtkSmartPointer<vtkMultiBlockDataSet>::New();
    _data_set->SetNumberOfBlocks(0);
    _mapper = vtkSmartPointer<vtkCompositePolyDataMapper>::New();

    vtkNew<vtkCompositeDataDisplayAttributes> attrs;

    _mapper->SetCompositeDataDisplayAttributes(attrs);
    _mapper->SetInputDataObject(_data_set);

    _actor = vtkSmartPointer<vtkActor>::New();
    _actor->SetMapper(_mapper);
}

scene::VtkCompositeSceneRenderer::id_type scene::VtkCompositeSceneRenderer::add_block(vtkSmartPointer<vtkPolyData> &poly_data)
{
    _source_data.insert_or_assign(_counter_id, poly_data);
    _instance_to_partition.insert_or_assign(_counter_id, _inserter_id);
    ++_inserter_id;
    ++_counter_id;

    return _counter_id;
}

void scene::VtkCompositeSceneRenderer::remove_block(id_type instance_id)
{
    if(!_instance_to_partition.contains(instance_id)) {
        throw std::runtime_error("Trying to remove a non-existing block!");
    }

    _source_data.erase(instance_id);    
}

void scene::VtkCompositeSceneRenderer::set_renderer(const vtkSmartPointer<vtkRenderer> &renderer)
{
    if(_renderer) {
        _renderer->RemoveActor(_actor);
    }

    _renderer = renderer;

    if(_actor) {
        _renderer->AddActor(_actor);
    }
}

void scene::VtkCompositeSceneRenderer::update()
{
    _inserter_id = 0;
    _instance_to_partition.clear();

    _data_set = vtkSmartPointer<vtkMultiBlockDataSet>::New();
    _data_set->SetNumberOfBlocks(_source_data.size());

    for(auto& [instance_key, instance_data] : _source_data) {
        _instance_to_partition.insert_or_assign(instance_key, _inserter_id);
        _data_set->SetBlock(_inserter_id, instance_data);
        ++_inserter_id;
    }

    _mapper->SetInputDataObject(_data_set);
    _mapper->StaticOn();

    _mapper->Update();

    _actor->SetMapper(_mapper);
}

void scene::VtkCompositeSceneRenderer::clear()
{
    _renderer->RemoveActor(_actor);
}

void scene::VtkCompositeSceneRenderer::set_color(id_type instance_id, common::Colord& color)
{
    if(!_instance_to_partition.contains(instance_id)) {
        throw std::runtime_error("Trying to modify non-existing block!");
    }

    auto internal_block_id = _instance_to_partition[instance_id];

    _mapper->SetBlockColor(internal_block_id, color);
    _mapper->Modified();
    _mapper->Update();
}
