#include "random.h"

#include <random>
#include <vector>

namespace txm {

    int random::minmax(int min, int max) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<int> distribution(min, max);
        return distribution(gen);
    }

    template <typename T>
    T random::element(std::vector<T> elements) {
        return elements[minmax(0, elements.size() - 1)];
    }

}
