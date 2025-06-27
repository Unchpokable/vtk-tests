#ifndef UNC_COMPOSITE_RENDERER_H
#define UNC_COMPOSITE_RENDERER_H

#include "common_types.hxx"

namespace scene
{
class CompositeRenderer
{
public:
    using id_type = vtkIdType;

    CompositeRenderer(id_type uid);

    /// @brief Adds a new polydata block
    /// @param poly_data block to be added
    /// @return unique internal identifier of added block. Should be used as block_id parameter in any modification
    /// function of \c this instance
    id_type add_block(vtkSmartPointer<vtkPolyData>& poly_data);

    /// @brief Removes a block bound to given instance id
    /// @param instance_id identifier of instance to be removed. Should be a unique global identifier (returned by \c
    /// add_block)
    void remove_block(id_type instance_id);

    void set_renderer(const vtkSmartPointer<vtkRenderer>& renderer);

    void update();
    void clear();

    void set_color(id_type instance_id, common::Colord& color);

    id_type get_instance_id(id_type block_id) const;

    vtkPolyData* get_instance_block(id_type instance_id) const;
    vtkPolyData* get_block(id_type block_id) const;

    id_type get_block_id(vtkPolyData* poly_data) const;

    void set_pickable(bool unabled);

    bool is_owns(vtkPolyData* poly_data) const;

    inline id_type self_id() const
    {
        return _uid;
    };

    inline vtkSmartPointer<vtkActor> actor() const
    {
        return _actor;
    }

    inline vtkSmartPointer<vtkRenderer> renderer() const
    {
        return _renderer;
    }

private:
    static constexpr const char* _uid_container_name = "uniq_id";
    static constexpr const char* _owner_id_container_name = "owner_id";

    void append_data_block(vtkPolyData* poly_data, const char* container_name, int data);

    const id_type _uid;

    id_type _counter_id { 0 };
    id_type _inserter_id { 0 };

    /// @brief maps global static registered block identifier to its partition inserter index
    std::unordered_map<id_type, id_type> _instance_to_block;

    /// @brief maps partition inserter index to global static registered block identifier
    std::unordered_map<id_type, id_type> _block_to_instance;

    /// @brief maps id of id_counter (global static registered block identifier) to its polydata
    std::unordered_map<id_type, vtkSmartPointer<vtkPolyData>> _source_data;

    vtkSmartPointer<vtkMultiBlockDataSet> _data_set;
    vtkSmartPointer<vtkCompositePolyDataMapper> _mapper;
    vtkSmartPointer<vtkActor> _actor;
    vtkSmartPointer<vtkRenderer> _renderer;
};
} // namespace scene

#endif // Composite Renderer
