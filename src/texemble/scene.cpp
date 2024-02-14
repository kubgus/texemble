#include "scene.h"

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
    void scene<width, height>::add(entity ent) {
        _entities.push_back(ent);
    }

    template <int width, int height>
    void scene<width, height>::begin() const {
        CLEAR();
    }

    template <int width, int height>
    void scene<width, height>::render() const {
        std::array<char, width * height> renderspace;
        for (int i = 0; i < _entities.size(); i++) {
            entity ent = _entities[i];
            for (int y = 0; y < ent.y; y++) {
                for (int x = 0; x < ent.x; x++) {
                    renderspace[(ent.y + y) * ent.spr.width + x] = ent.spr.chars[y * ent.spr.width + x];
                }
            }
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) std::cout << renderspace[y * width + x];
            std::cout << std::endl;
        }
    }

}
