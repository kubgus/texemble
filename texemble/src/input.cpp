#include "input.h"

#include <thread>

namespace txm {

    bool input::_running = false;

    std::thread input::listen() {
        _init();

        _running = true;
        return std::thread([&]() {
            while (_running) {
                char input = '\0';
#ifndef TXM_WINDOWS
                read(STDIN_FILENO, &input, 1);
#else
                if (_kbhit()) input = _getch();
#endif
                _queue.push(input);
            }

            _term();
        });
    }

    void input::finish() {
        _running = false;
    }

    void input::handle(std::function<void(char in)> handler) {
        _handler = handler;
    }

    void input::evaluate() {
        while (!_queue.empty()) {
            _handler(_queue.front());
            _queue.pop();
        }
    }

    void input::_init() {
#ifndef TXM_WINDOWS
        tcgetattr(STDIN_FILENO, &_st);
        _nd = _st;

        _nd.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &_nd);
#endif
    }

    void input::_term() {
#ifndef TXM_WINDOWS
        tcsetattr(STDIN_FILENO, TCSANOW, &_st);
#endif
    }
}
