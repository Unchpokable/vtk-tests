#include "pch.h"

#include "composite_renderer.hxx"
#include "utils.hxx"

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
    _instance_to_block.insert_or_assign(_counter_id, _inserter_id);
    ++_inserter_id;
    ++_counter_id;

    return _counter_id - 1;
}

void scene::VtkCompositeSceneRenderer::remove_block(id_type instance_id)
{
    if(!_instance_to_block.contains(instance_id)) {
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
    _instance_to_block.clear();

    _data_set = vtkSmartPointer<vtkMultiBlockDataSet>::New();
    _data_set->SetNumberOfBlocks(_source_data.size());

    for(auto& [instance_key, instance_data] : _source_data) {
        _instance_to_block.insert_or_assign(instance_key, _inserter_id);
        _data_set->SetBlock(_inserter_id, instance_data);
        ++_inserter_id;
    }

    _mapper->SetInputDataObject(_data_set);

    _mapper->Update();
}

void scene::VtkCompositeSceneRenderer::clear()
{
    _renderer->RemoveActor(_actor);
}

void scene::VtkCompositeSceneRenderer::set_color(id_type instance_id, common::Colord& color)
{
    if(!_instance_to_block.contains(instance_id)) {
        throw std::runtime_error("Trying to modify non-existing block!");
    }

    auto data = _source_data[instance_id];

    vtkNew<vtkUnsignedCharArray> colors;
    colors->SetNumberOfComponents(3);
    colors->SetName("Colors");
    
    auto color_array = utils::make_uchar_color(color);
    
    auto cells_count = data->GetNumberOfCells();

    colors->SetNumberOfTuples(cells_count);
    for (id_type i = 0; i < cells_count; ++i) {
        colors->SetTuple3(i, color_array[0], color_array[1], color_array[2]);
    }

    data->GetCellData()->SetScalars(colors);
    data->Modified();

    _mapper->Modified();
    _mapper->Update();
}
