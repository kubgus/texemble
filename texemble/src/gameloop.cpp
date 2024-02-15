#include "gameloop.h"

#include <thread>

namespace txm {

    bool gameloop::_running = false;
    int gameloop::_fps = 24;
    std::chrono::duration<double> gameloop::_framedur(1.0 / _fps);

    void gameloop::start(std::function<void()> fun) {
        _running = true;
        while (_running) {
            auto start = std::chrono::high_resolution_clock::now();

            fun();

            auto end = std::chrono::high_resolution_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            std::this_thread::sleep_for(_framedur - elapsed);
        }
    }

    void gameloop::end() {
        _running = false;
    }

    void gameloop::fpset(int framerate) {
        _fps = framerate;
        _framedur = std::chrono::duration<double>(1.0 / _fps);
    }

}
