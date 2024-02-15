#pragma once

#include <functional>
#include <thread>
#include <queue>

#ifndef TXM_WINDOWS
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#endif

namespace txm {

    class input {
    public:
        static std::thread listen();
        static void finish();

        static void handle(std::function<void(char in)> handler);

        static void evaluate();
    private:
        static bool _running;
        static inline std::queue<char> _queue;
        static inline std::function<void(char)> _handler;

#ifndef TXM_WINDOWS
        static inline struct termios _st, _nd;
#endif

        static inline void _init();
        static inline void _term();
    };

}
