#ifndef UNC_COMPOSITE_RENDERER_H
#define UNC_COMPOSITE_RENDERER_H

namespace scene
{
class VtkCompositeSceneRenderer 
{
public:
    using id_type = int;

    id_type add_block(vtkPolyData* polyData);
    bool remove_block(id_type block_id);

    const vtkActor* const render_to(vtkRenderer* renderer);
    void clear();

private:
    std::unordered_map<id_type, vtkPolyData*> _source_data;

    vtkSmartPointer<vtkActor> _actor;
};
}

#endif
