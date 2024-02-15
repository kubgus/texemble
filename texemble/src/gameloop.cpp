#include "gameloop.h"

#include <thread>

#include "input.h"

namespace txm {

    bool gameloop::_running = false;

    int gameloop::_fps = 24;
    std::chrono::duration<double> gameloop::_framedur(1.0 / _fps);

    void gameloop::start(std::function<void()> fun) {
        std::thread listener = input::listen();

        _running = true;
        while (_running) {
            auto start = std::chrono::high_resolution_clock::now();

            fun();

            input::evaluate();

            auto end = std::chrono::high_resolution_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            std::this_thread::sleep_for(_framedur - elapsed);
        }

        input::finish();
        if (listener.joinable()) listener.join();
    }

    void gameloop::stop() {
        _running = false;
    }

    void gameloop::setframerate(int fps) {
        _fps = fps;
        _framedur = std::chrono::duration<double>(1.0 / _fps);
    }

}
