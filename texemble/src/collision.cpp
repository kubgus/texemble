#include "collision.h"

namespace txm {

    bool collision::check(const entity& left, const entity& right) {
        int ltop = left.y;
        int lbottom = left.y + left.spr.height;
        int lleft = left.x;
        int lright = left.x + left.spr.width;

        int rtop = right.y;
        int rbottom = right.y + right.spr.height;
        int rleft = right.x;
        int rright = right.x + right.spr.width;

        return (lright > rleft && lleft < rright && lbottom > rtop && ltop < rbottom);
    }

}
