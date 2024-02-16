#pragma once

#include "entity.h"

namespace txm::collision {

    bool aabb(const entity& left, const entity& right);

    bool charcol(const entity& left, const entity& right);

}
