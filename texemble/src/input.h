#pragma once

#include <functional>
#include <thread>

#ifndef TXM_WINDOWS
#include <termios.h>
#include <unistd.h>
#else
#include <conio.h>
#endif

namespace txm {

    class input {
    public:
        static void handle(std::function<void(char latest)> handle);
        static void finish();
    private:
        static bool _running;
        static inline std::thread _handler;

#ifndef TXM_WINDOWS
        static inline struct termios _st, _nd;
#endif

        static inline void _init();
        static inline void _term();
    };

}
