#pragma once

#include <chrono>
#include <functional>

namespace txm {
    
    class gameloop {
    public:
        static void start(std::function<void()> fun);

        static void fpset(int fps);
    private:
        static int fps;
        static std::chrono::duration<double> framedur;
    };

}
