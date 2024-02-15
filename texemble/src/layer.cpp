#include "layer.h"

#include <algorithm>
#include <vector>

#include "entity.h"

namespace txm {

    template <int width, int height>
    layer<width, height>::~layer() {
        for (entity* ent : _entities) delete ent;
    }

    template <int width, int height>
    void layer<width, height>::add(entity* entity) {
        _entities.push_back(entity);
        home->add(entity);
    }

    template <int width, int height>
    void layer<width, height>::remove(entity* entity) {
        if (home->contains(entity))
            home->remove(entity);
        auto it = std::find(_entities.begin(), _entities.end(), entity);
        if (it != _entities.end()) _entities.erase(it);
        delete entity;
    }
        
}
