#include "pch.h"

#include "composite_renderer.hxx"

scene::VtkCompositeSceneRenderer::id_type scene::VtkCompositeSceneRenderer::add_block(vtkPolyData *polyData)
{
    return id_type();
}

bool scene::VtkCompositeSceneRenderer::remove_block(id_type block_id)
{
    return false;
}

const vtkActor *const scene::VtkCompositeSceneRenderer::render_to(vtkRenderer *renderer)
{
    return nullptr;
}

void scene::VtkCompositeSceneRenderer::clear() 
{

}
