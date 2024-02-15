#pragma once

#include "entity.h"

namespace txm {

    class collision {
    public:
        static bool check(const entity& left, const entity& right);
    };

}
