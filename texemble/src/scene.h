#pragma once

#include <vector>

#include "entity.h"

namespace txm {

    template <int width, int height>
    class scene {
    public:
        inline void add(entity* ent);

        inline void clear() const;
        void render() const;
    private:
        std::vector<entity*> _entities;
    };

}
