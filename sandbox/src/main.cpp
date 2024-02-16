#include <texemble.h>

#define WIDTH 64
#define HEIGHT 32

int main() {
    txm::scene<WIDTH, HEIGHT> myscene;

    txm::sprite basket = { 5, 3, {
        "/~~~\\",
        "UUUUU",
        " UUU ",
    }};

    txm::sprite cherry = { 3, 4, {
        " / ",
        "OOO",
        "OOO",
        "OOO",
    }};

    txm::sprite watermelon = { 4, 3, {
        "----",
        "\\WW/",
        " -- ",
    }};

    txm::sprite bomb = { 3, 4, {
        " ! ",
        " B ",
        "BBB",
        " B ",
    }};

    txm::entity player = { WIDTH / 2 + 3, HEIGHT - 5, basket };
    myscene.add(&player);

    txm::layer enemies = &myscene;

    txm::input::handle([&](char in) {
        if (in == 'a') player.x--;
        if (in == 'd') player.x++;

        if (in == 'q') txm::gameloop::stop();
    });

    int score = 0;

    int difficulty = 240;
    int spawnrate = 48;
    int gravity = 12;

    int framecount = 0; 
    txm::gameloop::setframerate(24);
    txm::gameloop::start([&]() {
 
        myscene.clear();

        std::cout << "SCORE: " << score << "  ENDLESS: " << framecount / 24 << std::endl;

        if (framecount % spawnrate == 0)
            enemies.add(new txm::entity {
                txm::random::minmax(0, WIDTH - 5), 2,
                txm::random::element<txm::sprite>({ cherry, watermelon, bomb })
            });


        for (int i = 0; i < enemies.list().size(); i++) {
            txm::entity* ent = enemies.list()[i];
            if (framecount % gravity == 0) ent->y++;
            bool danger = ent->s.c[1] == '!' ? true : false;
            if (ent->y >= HEIGHT) {
                if (danger) enemies.remove(ent);
                else {
                    txm::gameloop::stop();
                    std::cout << "FAILED!" << std::endl;
                }
            }
            if (txm::collision::aabb(player, *ent)) {
                if (danger) {
                    txm::gameloop::stop();
                    std::cout << "BOOM!" << std::endl;
                } else {
                    enemies.remove(ent);
                    score++;
                }
            }
        }

        if (framecount % difficulty == 0) {
            spawnrate -= spawnrate - 4 == 0 ? 0 : 4;
            gravity -= gravity - 2 == 0 ? 0 : 2;
        }

        myscene.render();

        framecount++;

    });
}
