#pragma once

#include <string>
#include <vector>

namespace txm {

    struct sprite {
        int w, h;
        std::vector<char> c;

        sprite(int w, int h, std::string s)
            : w(w), h(h) {
            for (char x : s) c.push_back(x);
        }

        sprite(int w, int h, std::vector<std::string> ss)
            : w(w), h(h) {
            for (std::string s : ss)
                for (char x : s) c.push_back(x);
        }
    };

}
