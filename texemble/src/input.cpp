#include "input.h"

namespace txm {

    input::input() {
        tcgetattr(STDIN_FILENO, &_st);
        _nd = _st;

        _nd.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &_nd);
    }

    input::~input() {
        tcsetattr(STDIN_FILENO, TCSANOW, &_st);

        _handler.join();
    }


    void input::handle(std::function<void(char latest)> handle) {
        _handler = std::thread([&]() {
            while (true) {
                char input = '\0';
                read(STDIN_FILENO, &input, 1);
                handle(input);
            }
        });
    }

}
