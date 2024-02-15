#pragma once

#include <set>

#include "entity.h"

namespace txm {

    template <int width, int height>
    class scene {
    public:
        inline void add(entity* ent);
        inline void remove(entity* ent);

        inline bool contains(entity* ent);
        inline std::set<entity*> list();

        inline void clear() const;
        void render() const;
    private:
        std::set<entity*> _entities;
    };

}
