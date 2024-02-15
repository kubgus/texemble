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

    txm::sprite stickman = { 3, 3, {
        " O ",
        "/|\\",
        "/ \\",
    }};

    txm::sprite rock = { 3, 3, {
        " # ",
        "## ",
        "###",
    }};

    txm::entity player = { WIDTH / 2, HEIGHT / 2, stickman };
    myscene.add(&player);

    txm::layer obstacles = &myscene;
    obstacles.add(new txm::entity { 20, 16, rock });
    obstacles.add(new txm::entity { 53, 6, rock });
    obstacles.add(new txm::entity { 15, 24, rock });
    obstacles.add(new txm::entity { 34, 29, rock });

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

        myscene.render(player.x - WIDTH / 2, player.y - HEIGHT / 2);

    });
}
