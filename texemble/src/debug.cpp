#include "debug.h"

#include <iostream>

namespace txm {

    template <typename... A>
    void debug::lineout(A... args) {
        (std::cout << ... << args) << std::endl;
    }

    template <typename... A>
    void debug::debugout(A... args) {
#ifdef TXM_DEBUG
        lineout(args...);
#endif
    }

}
