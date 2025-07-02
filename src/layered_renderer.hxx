#include "composite_scene_object.hxx"

#include "composite_scene_globals.hxx"

namespace scene
{
class LayeredRenderer
{
    struct SceneIndex
    {
        id_type layer_id;
        id_type prop_id;
    };

    explicit LayeredRenderer();

    /// @brief Adds a new layer on top
    /// @return ID of new created layer
    id_type push_layer();

    /// @brief Removes a last added layer from top.
    /// @return ID of layer which is top layer now
    id_type pop_layer();

    SceneIndex add_prop(id_type layer_id, vtkSmartPointer<vtkProp3D>& prop);
    void remove_prop(id_type layer_id, id_type prop_id);

    void move_prop(id_type prop_id, id_type from_layer, id_type to_layer);

    vtkProp3D* get_prop(id_type layer_id, id_type prop_id);
    vtkProp3D* take_prop(id_type layer_id, id_type prop_id);

    void reset_clipping_range();

    id_type get_layers_count() const;
    vtkSmartPointer<vtkRenderer> get_layer(id_type id) const;

    vtkSmartPointer<vtkRenderer> get_base_layer() const;

private:
    bool has_layer(id_type layer_id) const;
    bool has_prop(id_type layer_id, id_type prop_id) const;

    id_type _layers_count;
    id_type _layers_inserter_index;

    std::unordered_map<id_type, vtkSmartPointer<vtkRenderer>> _layers;

    /// @brief maps layers id to its inserter counter;
    std::unordered_map<id_type, id_type> _prop_inserter_indexes;

    /// @brief Maps a layer id to its actors collection
    std::unordered_map<id_type, std::unordered_map<id_type, vtkSmartPointer<vtkProp3D>>> _layered_props;

    vtkSmartPointer<vtkRenderer> _base_renderer;
    vtkSmartPointer<vtkRenderWindow> _window;
};
} // namespace scene