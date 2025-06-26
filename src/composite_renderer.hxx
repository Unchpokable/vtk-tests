#ifndef UNC_COMPOSITE_RENDERER_H
#define UNC_COMPOSITE_RENDERER_H

#include "common_types.hxx"

namespace scene
{
class VtkCompositeSceneRenderer 
{
public:
    using id_type = vtkIdType;

    VtkCompositeSceneRenderer();

    /// @brief Adds a new polydata block
    /// @param poly_data block to be added
    /// @return unique internal identifier of added block. Should be used as block_id parameter in any modification function of \c this instance
    id_type add_block(vtkSmartPointer<vtkPolyData>& poly_data);

    /// @brief Removes a block bound to given instance id
    /// @param instance_id identifier of instance to be removed. Should be a unique global identifier (returned by \c add_block)
    void remove_block(id_type instance_id);

    void set_renderer(const vtkSmartPointer<vtkRenderer>& renderer);
    
    void update();
    void clear();

    void set_color(id_type instance_id, common::Colord& color);

    id_type get_instance_id(id_type block_id);

    const vtkPolyData* get_block(id_type block_id);
    const vtkPolyData* get_instance_block(id_type instance_id);

private:
    id_type _counter_id { 0 };
    id_type _inserter_id { 0 };

    /// @brief maps global static registered block identifier to its partition inserter index
    std::unordered_map<id_type, id_type> _instance_to_block;

    /// @brief maps id of id_counter (global static registered block identifier) to its polydata
    std::unordered_map<id_type, vtkSmartPointer<vtkPolyData>> _source_data;

    vtkSmartPointer<vtkMultiBlockDataSet> _data_set;
    vtkSmartPointer<vtkCompositePolyDataMapper> _mapper;
    vtkSmartPointer<vtkActor> _actor;
    vtkSmartPointer<vtkRenderer> _renderer;
};
}

#endif // Composite Renderer
