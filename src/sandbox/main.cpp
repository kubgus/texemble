#include <iostream>

#include <texemble.h>

int main() {
    txm::scene myscene = { 64, 128 };

    std::cout << myscene.dimensions().x << std::endl;
}
