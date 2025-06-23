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

    id_type add_block(vtkSmartPointer<vtkPolyData>& poly_data);
    void remove_block(id_type block_id);

    void set_renderer(const vtkSmartPointer<vtkRenderer>& renderer);
    
    void update();
    void clear();

    void set_color(id_type block_id, common::Colord& color);

private:
    void rebuild_actor();

    id_type _counter_id { 0 };
    id_type _inserter_id { 0 };

    /// @brief maps global static registered block identifier to its partition inserter index
    std::unordered_map<id_type, id_type> _instance_to_partition;

    /// @brief maps id of id_counter (global static registered block identifier) to its polydata
    std::unordered_map<id_type, vtkSmartPointer<vtkPolyData>> _source_data;

    vtkSmartPointer<vtkPartitionedDataSet> _data_set;
    vtkSmartPointer<vtkCompositePolyDataMapper> _mapper;
    vtkSmartPointer<vtkActor> _actor;
    vtkSmartPointer<vtkRenderer> _renderer;
};
}

#endif // Composite Renderer
