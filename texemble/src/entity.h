#pragma once

#include "sprite.h"

namespace txm {
    
    struct entity {
        int x, y;
        sprite s;

        inline int w() const { return s.w; }
        inline int h() const { return s.h; }
    };

}
