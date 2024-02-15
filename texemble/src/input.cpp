#include "input.h"

namespace txm {

    input::input() {
#ifndef TXM_WINDOWS
        tcgetattr(STDIN_FILENO, &_st);
        _nd = _st;

        _nd.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &_nd);
#endif
    }

    input::~input() {
#ifndef TXM_WINDOWS
        tcsetattr(STDIN_FILENO, TCSANOW, &_st);
#endif

        _handler.join();
    }


    void input::handle(std::function<void(char latest)> handle) {
        _running = true;
        _handler = std::thread([&]() {
            while (_running) {
            char input = '\0';
#ifndef TXM_WINDOWS
                read(STDIN_FILENO, &input, 1);
#else
                if (_kbhit()) input = _getch();
#endif
                handle(input);
            }
        });
    }

    void input::exit() {
        _running = false;
    }

}
