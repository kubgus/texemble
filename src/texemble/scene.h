#pragma once

#include <vector>

#include "entity.h"

namespace txm {

    template <int width, int height>
    class scene {
    public:
        void add(entity ent);

        void begin() const;
        void render() const;
    private:
        std::vector<entity> _entities;
    };

}
