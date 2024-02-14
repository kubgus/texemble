#include "gameloop.h"

#include <thread>

namespace txm {

    int gameloop::fps = 24;
    std::chrono::duration<double> gameloop::framedur(1.0 / fps);

    void gameloop::start(std::function<void()> fun) {
        while (true) {
            auto start = std::chrono::high_resolution_clock::now();

            fun();

            auto end = std::chrono::high_resolution_clock::now();

            auto elapsed = std::chrono::duration_cast<std::chrono::duration<double>>(end - start);
            std::this_thread::sleep_for(framedur - elapsed);
        }
    }

    void gameloop::fpset(int framerate) {
        fps = framerate;
        framedur = std::chrono::duration<double>(1.0 / fps);
    }

}
