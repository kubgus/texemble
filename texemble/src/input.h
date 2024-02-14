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
        input();
        ~input();

        void handle(std::function<void(char latest)> handle);
    private:
        std::thread _handler;
#ifndef TXM_WINDOWS
        struct termios _st, _nd;
#endif
    };

}
