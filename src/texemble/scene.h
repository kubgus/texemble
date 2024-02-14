#pragma once

#include "vec2.h"

namespace txm {

    class scene {
    public:
        scene(int width, int height)
            : _width(width), _height(height) {}

        inline vec2 dimensions() const { return _dim; }
    private:
        union {
            vec2 _dim;
            struct {
                int _width, _height;
            };
        };
    };

}
