#pragma once

#include <chrono>
#include <functional>

namespace txm {
    
    class gameloop {
    public:
        static void start(std::function<void()> fun);
        static void end();

        static void fpset(int fps);
    private:
        static bool _running;
        static int _fps;
        static std::chrono::duration<double> _framedur;
    };

}
