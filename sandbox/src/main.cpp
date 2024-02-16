#include <texemble.h>

#define WIDTH 64
#define HEIGHT 32

int main() {
    txm::scene<WIDTH, HEIGHT> myscene;

    txm::sprite block1 = { 2, 3, {
        "##",
        " #",
        " #",
    }};

    txm::sprite block2 = { 3, 2, " # ###"};

    txm::entity player = { 10, 10, block1 };
    myscene.add(&player);

    txm::entity block = { 5, 5, block2 };
    myscene.add(&block);

    txm::input::handle([&](char in) {
        if (in == 'w') player.y--;
        if (in == 's') player.y++;
        if (in == 'a') player.x--;
        if (in == 'd') player.x++;

        if (in == 'q') txm::gameloop::stop();
    });

    int framecount = 0; 
    txm::gameloop::setframerate(24);
    txm::gameloop::start([&]() {
 
        myscene.clear();

        txm::debug::lineout("Collision is ", txm::collision::charcol(player, block) ? "" : "not");

        myscene.render();

        framecount++;

    });
}
