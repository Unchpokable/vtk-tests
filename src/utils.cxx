#include "pch.h"

#include "utils.hxx"

constexpr std::array<unsigned char, 3> utils::make_uchar_color(common::Colord& color)
{
    auto data = (double*)color;

    return {
        static_cast<unsigned char>(color[0] * 255), 
        static_cast<unsigned char>(color[1] * 255), 
        static_cast<unsigned char>(color[2] * 255)
    };
}
