#include "pch.hxx"

#include "composite_scene_object.hxx"
#include "utils.hxx"

scene::CompositeSceneObject::CompositeSceneObject(id_type uid) : _uid(uid)
{
    _data_set = vtkSmartPointer<vtkMultiBlockDataSet>::New();
    _data_set->SetNumberOfBlocks(0);
    _mapper = vtkSmartPointer<vtkCompositePolyDataMapper>::New();

    vtkNew<vtkCompositeDataDisplayAttributes> attrs;

    _mapper->SetCompositeDataDisplayAttributes(attrs);
    _mapper->SetInputDataObject(_data_set);

    _actor = vtkSmartPointer<vtkActor>::New();
    _actor->SetMapper(_mapper);

    _actor->PickableOn();
}

scene::id_type scene::CompositeSceneObject::add_block(vtkSmartPointer<vtkPolyData>& poly_data)
{
    _source_data.insert_or_assign(_counter_id, poly_data);
    _instance_to_block.insert_or_assign(_counter_id, _inserter_id);
    _block_to_instance.insert_or_assign(_inserter_id, _counter_id);
    ++_inserter_id;

    append_data_block(poly_data, _uid_container_name, _counter_id);
    append_data_block(poly_data, _owner_id_container_name, _uid);

    ++_counter_id;

    return _counter_id - 1;
}

void scene::CompositeSceneObject::remove_block(id_type instance_id)
{
    if(!_instance_to_block.contains(instance_id)) {
        throw std::runtime_error("Trying to remove a non-existing block!");
    }

    auto block_id = _instance_to_block[instance_id];
    _source_data.erase(instance_id);
    _instance_to_block.erase(instance_id);
    _block_to_instance.erase(block_id);
}

void scene::CompositeSceneObject::set_renderer(const vtkSmartPointer<vtkRenderer>& renderer)
{
    if(_renderer) {
        _renderer->RemoveActor(_actor);
    }

    _renderer = renderer;

    if(_actor) {
        _renderer->AddActor(_actor);
    }
}

void scene::CompositeSceneObject::update()
{
    _inserter_id = 0;
    _instance_to_block.clear();
    _block_to_instance.clear();

    _data_set = vtkSmartPointer<vtkMultiBlockDataSet>::New();
    _data_set->SetNumberOfBlocks(_source_data.size());

    for(auto& [instance_key, instance_data] : _source_data) {
        _instance_to_block.insert_or_assign(instance_key, _inserter_id);
        _block_to_instance.insert_or_assign(_inserter_id, instance_key);
        _data_set->SetBlock(_inserter_id, instance_data);
        ++_inserter_id;
    }

    _mapper->SetInputDataObject(_data_set);

    _mapper->Update();
}

void scene::CompositeSceneObject::clear()
{
    _renderer->RemoveActor(_actor);
}

void scene::CompositeSceneObject::set_color(id_type instance_id, common::Colord& color)
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
    for(id_type i = 0; i < cells_count; ++i) {
        colors->SetTuple3(i, color_array[0], color_array[1], color_array[2]);
    }

    data->GetCellData()->SetScalars(colors);
    data->Modified();

    _mapper->Modified();
    _mapper->Update();
}

scene::id_type scene::CompositeSceneObject::get_instance_id(id_type block_id) const
{
    return _block_to_instance.at(block_id);
}

vtkPolyData* scene::CompositeSceneObject::get_instance_block(id_type instance_id) const
{
    if(!_source_data.contains(instance_id)) {
        throw std::runtime_error("Trying to get a non-existing instance");
    }

    return _source_data.at(instance_id);
}

vtkPolyData* scene::CompositeSceneObject::get_block(id_type block_id) const
{
    if(!_block_to_instance.contains(block_id)) {
        throw std::runtime_error("Trying to get a non-existing block");
    }

    auto instance_id = _block_to_instance.at(block_id);
    return _source_data.at(instance_id);
}

scene::id_type scene::CompositeSceneObject::get_block_id(vtkPolyData* poly_data) const
{
    auto data = poly_data->GetCellData();

    auto owner_id_contaier = data->GetAbstractArray(_owner_id_container_name);

    if(!owner_id_contaier) {
        return -1;
    }

    auto data_array = vtkIntArray::SafeDownCast(owner_id_contaier);
    if(!data_array || data_array->GetNumberOfComponents() < 1) {
        return -1;
    }

    auto value = data_array->GetValue(0);

    return value;
}

void scene::CompositeSceneObject::set_pickable(bool enabled)
{
    _actor->SetPickable(enabled);
}

bool scene::CompositeSceneObject::is_owns(vtkPolyData* poly_data) const
{
    auto id = get_block_id(poly_data);
    if(id == -1) {
        return false;
    }

    return id == _uid;
}

void scene::CompositeSceneObject::append_data_block(vtkPolyData* poly_data, const char* container_name, int data)
{
    vtkNew<vtkIntArray> container;
    container->SetName(container_name);

    for(auto i { 0 }; i < poly_data->GetNumberOfCells(); ++i) {
        container->InsertNextValue(data);
    }

    poly_data->GetCellData()->AddArray(container);
}
