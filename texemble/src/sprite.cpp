#include "sprite.h"

#include <vector>

namespace txm {

    void sprite::rotate(direction dir) {
        std::vector<char> n;
        n.resize(w * h);
        for (int y = 0; y < h; y++)
            for (int x = 0; x < w; x++)
                switch (dir) {
                    case LEFT:
                        n[(w - 1 - x) * h + y] = c[y * w + x];
                        break;
                    case RIGHT:
                        n[x * h + (h - 1 - y)] = c[y * w + x];
                }
        c = n;

        int t = w;
        w = h;
        h = t;
    }

}
