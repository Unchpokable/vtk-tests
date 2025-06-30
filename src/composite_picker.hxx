#include "composite_scene_globals.hxx"
#include "composite_scene_object.hxx"

namespace scene
{
namespace pick
{
constexpr scene::id_type NO_PICK = -1;

/// @brief Performs a pick from target composite renderer and returns picked instance id
/// @param target CompositeObject to be a pick target
/// @param screen_pos Position of cursor on screen
/// @return instance id of picked block from target composite renderer or NO_PICK constant if there is no block picked
scene::id_type perform_pick(const CompositeSceneObject& target, common::Vec3d screen_pos);
} // namespace pick
} // namespace scene
