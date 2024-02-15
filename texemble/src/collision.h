#pragma once

#include "entity.h"

namespace txm {

    class collision {
    public:
        static bool aabb(const entity& left, const entity& right);
    };

}
