#pragma once

#include <functional>
#include <thread>
#include <termios.h>
#include <unistd.h>

namespace txm {

    class input {
    public:
        input();
        ~input();

        void handle(std::function<void(char latest)> handle);
    private:
        std::thread _handler;
        struct termios _st, _nd;
    };

}
