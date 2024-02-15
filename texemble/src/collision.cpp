#include "collision.h"

namespace txm {

    bool collision::aabb(const entity& left, const entity& right) {
        int ltop = left.y;
        int lbottom = left.y + left.h();
        int lleft = left.x;
        int lright = left.x + left.w();

        int rtop = right.y;
        int rbottom = right.y + right.h();
        int rleft = right.x;
        int rright = right.x + right.w();

        return (lright > rleft && lleft < rright && lbottom > rtop && ltop < rbottom);
    }

}
