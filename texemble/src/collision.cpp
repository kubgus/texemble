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

    bool collision::charcol(const entity& left, const entity& right) {
        if (!aabb(left, right)) return false;

        for (int l = 0; l < left.s.w * left.s.h; l++) {
            if (left.s.c[l] == ' ') continue;
            int offx = left.x + (l % left.w()) - right.x;
            int offy = left.y + (l / left.w()) - right.y;
            if (left.s.c[l * left.w() + (l % left.w())] == ' ') continue;
            if (offx >= 0 && offx < right.w() && offy >= 0 && offy < right.h() && right.s.c[offy * right.w() + offx] != ' ')
                return true;
        }

        return false;
    }

}
