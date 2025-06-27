#include "composite_renderer.hxx"

namespace scene
{
namespace pick
{
constexpr CompositeRenderer::id_type NO_PICK = -1;

/// @brief Performs a pick from target composite renderer and returns picked instance id
/// @param renderer CompositeRenderer to be a pick target
/// @param screen_pos Position of cursor on screen
/// @return instance id of picked block from target composite renderer or NO_PICK constant if there is no block picked
CompositeRenderer::id_type perform_pick(const CompositeRenderer& renderer, common::Vec3d screen_pos);
} // namespace pick
} // namespace scene
