#pragma once

#include <chrono>
#include <functional>

namespace txm {
    
    class gameloop {
    public:
        static void start(std::function<void()> fun);
        static void stop();

        static void setframerate(int fps);
    private:
        static bool _running;

        static int _fps;
        static std::chrono::duration<double> _framedur;
    };

}
