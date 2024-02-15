#pragma once

#include <vector>

#include "entity.h"
#include "scene.h"

namespace txm {

    template <int width, int height>
    class layer {
    public:
        scene<width, height>* home;

        layer(scene<width, height>* home)
            : home(home) {}
        ~layer();
        
        void add(entity* entity);
        void remove(entity* entity);
        void removeall();

        inline const std::vector<entity*>& list() const { return _entities; }
    private:
        std::vector<entity*> _entities;
    };

}
