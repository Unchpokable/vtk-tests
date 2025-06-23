#include "pch.h"

#include "composite_renderer.hxx"

scene::VtkCompositeSceneRenderer::VtkCompositeSceneRenderer()
{
    _data_set = vtkSmartPointer<vtkPartitionedDataSet>::New();
    _data_set->SetNumberOfPartitions(0);
    _mapper = vtkSmartPointer<vtkCompositePolyDataMapper>::New();

    _mapper->SetInputDataObject(_data_set);
}

scene::VtkCompositeSceneRenderer::id_type scene::VtkCompositeSceneRenderer::add_block(vtkSmartPointer<vtkPolyData> &poly_data)
{
    _data_set->SetPartition(_inserter_id, poly_data);
    _source_data.insert_or_assign(_counter_id, poly_data);
    _instance_to_partition.insert_or_assign(_counter_id, _inserter_id);
    ++_inserter_id;
    ++_counter_id;

    return _counter_id;
}

void scene::VtkCompositeSceneRenderer::remove_block(id_type block_id)
{
    _inserter_id = 0;
    _instance_to_partition.clear();
    _source_data.erase(block_id);

    _data_set = vtkSmartPointer<vtkPartitionedDataSet>::New();

    for(auto& block_data : _source_data | std::views::values) {
        add_block(block_data);
    }
}

void scene::VtkCompositeSceneRenderer::set_renderer(vtkSmartPointer<vtkRenderer> &renderer)
{
    _renderer = renderer;
}

void scene::VtkCompositeSceneRenderer::clear() 
{
    _renderer->RemoveActor(_actor);
}

void scene::VtkCompositeSceneRenderer::set_color(id_type block_id, common::Colord& color)
{
    auto poly_data = _source_data[block_id];
}

void scene::VtkCompositeSceneRenderer::rebuild_actor()
{
}
