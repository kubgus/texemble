#include <texemble.h>

#define WIDTH 64
#define HEIGHT 32

int main() {
    txm::scene<WIDTH, HEIGHT> myscene;

    txm::entity player = { 0, 0, txm::sprite { 2, 2, {
        'x', 'x',
        'x', 'x',
    }}};

    myscene.add(&player);

    txm::input in;
    in.handle([&](char input) {
        if (input == 'w') player.y--;
        if (input == 's') player.y++;
        if (input == 'a') player.x--;
        if (input == 'd') player.x++;
    });

    int framecount = 0;
    txm::gameloop::fpset(24);
    txm::gameloop::start([&]() {

        myscene.begin();
        
        myscene.render();

        framecount++;

    });
}
