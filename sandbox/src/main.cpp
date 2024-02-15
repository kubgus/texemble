#include <texemble.h>

#include <random>

#define WIDTH 64
#define HEIGHT 32

int random(int min, int max) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(gen);
}

int main() {
    txm::scene<WIDTH, HEIGHT> myscene;

    txm::sprite block = { 1, 1, { '#' }};
    txm::sprite fruit = { 1, 1, { '*' }};

    txm::entity player = { 32, 16, block };
    txm::entity reward = { random(0, WIDTH - 1), random(0, HEIGHT - 1), fruit };

    myscene.add(&player);
    myscene.add(&reward);

    txm::input in;
    in.handle([&](char input) {
        if (input == 'k') player.y--;
        if (input == 'j') player.y++;
        if (input == 'h') player.x--;
        if (input == 'l') player.x++;

        if (input == 'q') {
            in.exit();
            txm::gameloop::end();
        }
    });

    int framecount = 0;
    txm::gameloop::fpset(24);
    txm::gameloop::start([&]() {

        myscene.begin();

        if (txm::collision::check(player, reward)) {
            reward.x = random(0, WIDTH - 1);
            reward.y = random(0, HEIGHT - 1);
        }

        myscene.render();

        framecount++;

    });
}
