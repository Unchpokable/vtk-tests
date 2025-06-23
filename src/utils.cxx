#include "pch.h"

#include "utils.hxx"

constexpr std::array<unsigned char, 3> utils::make_uchar_color(common::Colord& color)
{
    return {
        color.r() * 255, color.g() * 255, color.b() * 255
    };
}
