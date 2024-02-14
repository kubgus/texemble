#include <texemble.h>

#define WIDTH 64
#define HEIGHT 128

int main() {
    txm::scene<WIDTH, HEIGHT> myscene;

    txm::entity player = { 0, 0, txm::sprite { 2, 2, {
        'x', 'x',
        'x', 'x',
    }}};

    myscene.add(player);

    while (true) {

        myscene.begin();
        
        player.x += 1;

        myscene.render();

    }
}
