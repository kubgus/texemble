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
    inline void scene<width, height>::add(entity* ent) {
        _entities.push_back(ent);
    }

    template <int width, int height>
    inline void scene<width, height>::begin() const {
        CLEAR();
    }

    template <int width, int height>
    void scene<width, height>::render() const {
        std::array<char, width * height> renderspace;
        renderspace.fill(' ');
        for (int i = 0; i < _entities.size(); i++) {
            entity ent = *_entities[i];
            for (int y = 0; y < ent.spr.height; y++) {
                for (int x = 0; x < ent.spr.width; x++) {
                    const int chardown = ((ent.y + y) % height) * width;
                    const int charright = (ent.x + x) % width;
                    renderspace[chardown + charright] = ent.spr.chars[y * ent.spr.width + x];
                }
            }
        }

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) std::cout << renderspace[y * width + x];
            std::cout << std::endl;
        }
    }
}
