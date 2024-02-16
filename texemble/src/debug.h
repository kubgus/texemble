#pragma once

namespace txm {

    class debug {
    public:
        template <typename... A>
        static inline void lineout(A... args);

        template <typename... A>
        static inline void debugout(A... args);
    };

}
