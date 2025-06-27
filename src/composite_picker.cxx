#include "pch.h"

#include "composite_picker.hxx"

scene::CompositeRenderer::id_type scene::pick::perform_pick(const CompositeRenderer& renderer, common::Vec3d screen_pos)
{
    vtkNew<vtkCellPicker> picker;
    picker->PickFromListOn();
    picker->AddPickList(renderer.actor());

    screen_pos.z() = 0;

    auto picked = picker->Pick(screen_pos.x(), screen_pos.y(), screen_pos.z(), renderer.renderer());

    if(picked == 0) {
        return NO_PICK;
    }

    auto picked_data = picker->GetDataSet();

    auto poly_data = vtkPolyData::SafeDownCast(picked_data);

    if(renderer.is_owns(poly_data)) {
        auto block_id = renderer.get_block_id(poly_data);
        return renderer.get_instance_id(block_id);
    }

    return NO_PICK;
}
