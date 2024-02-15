#include "scene.h"

#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>

#include "entity.h"

#ifdef WINDOWS
#define CLEAR() system("cls")
#else
#define CLEAR() system("clear")
#endif

namespace txm {

    template <int width, int height>
    void scene<width, height>::add(entity* ent) {
        _entities.insert(ent);
    }

    template <int width, int height>
    void scene<width, height>::remove(entity* ent) {
        auto element = std::find(_entities.begin(), _entities.end(), ent);
        if (element != _entities.end()) _entities.erase(element);
    }

    template <int width, int height>
    bool scene<width, height>::contains(entity* ent) {
        return (std::find(_entities.begin(), _entities.end(), ent) != _entities.end());
    }

    template <int width, int height>
    std::set<entity*> scene<width, height>::list() {
        return _entities;
    }

    template <int width, int height>
    void scene<width, height>::clear() const {
        CLEAR();
    }

    template <int width, int height>
    void scene<width, height>::render(int offx, int offy) const {
        std::array<char, width * height> viewport;
        viewport.fill(' ');
        for (const auto& ent : _entities) {
            for (int y = 0; y < ent->h(); y++) {
                const int down = ent->y + y - offy;
                if (down < 0 || down >= height) continue;
                for (int x = 0; x < ent->w(); x++) {
                    const int right = ent->x + x - offx;
                    if (right < 0 || right >= width) continue;
                    viewport[down * width + right] = ent->s.c[y * ent->w() + x];
                }
            }
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) std::cout << viewport[y * width + x];
            std::cout << std::endl;
        }
    }
}
