#pragma once

#include <array>

#include "vec2.h"

namespace txm {

    template <int width, int height>
    struct sprite {
        std::array<char, width * height> chars;

        sprite(std::array<std::array<char, width>, height> multi) {
            for (int y = 0; y < height; y++) {
                const int moveby = y * width;
                for (int x = 0; x < width; x++)
                   chars[moveby + x] = multi[y][x];
            }
        }
    };

}
