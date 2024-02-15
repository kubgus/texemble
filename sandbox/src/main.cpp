#include <texemble.h>

#include <random>
#include <vector>

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

    txm::sprite plane = { 5, 3, {
        "  T  ",
        "<=I=>",
        "  -  ",
    }};

    txm::sprite bullet = { 1, 1, "*"};

    txm::sprite asteroid = { 2, 2, "####"};

    txm::entity player = { WIDTH / 2, HEIGHT / 2, plane };
    myscene.add(&player);

    txm::layer projectiles = &myscene;
    txm::layer enemies = &myscene;

    txm::input::handle([&](char in) {
        if (in == 'w') player.y--;
        if (in == 's') player.y++;
        if (in == 'a') player.x--;
        if (in == 'd') player.x++;

        if (in == ' ') projectiles.add(new txm::entity { player.x + 2, player.y, bullet});

        if (in == 'q') txm::gameloop::stop();
    });

    int score = 0;
    const int goal = 10;

    int framecount = 0;
    txm::gameloop::setframerate(24);
    txm::gameloop::start([&]() {

        myscene.clear();

        std::cout << "SCORE: " << score << "/" << goal << std::endl;

        if (framecount % 64 == 0)
            enemies.add(new txm::entity { random(0, WIDTH - 1), 0, asteroid });

        for (txm::entity* projectile : projectiles.list()) {
            if (!myscene.contains(projectile)) myscene.add(projectile);
            projectile->y--;

            if (projectile->y <= 0) {
                projectiles.remove(projectile);
                continue;
            }
        }

        for (txm::entity* enemy : enemies.list()) {
            if (framecount % 4 == 0) enemy->y++;

            if (enemy->y > HEIGHT - 2) {
                score--;
                enemies.remove(enemy);
            }

            for (txm::entity* projectile : projectiles.list()) {
                if (txm::collision::aabb(*projectile, *enemy)) {
                    score++;
                    enemies.remove(enemy);
                    break;
                }
            }
            
            if (txm::collision::aabb(player, *enemy)) {
                txm::gameloop::stop();
                std::cout << "YOU LOST!" << std::endl;
            }

            if (score == goal) {
                txm::gameloop::stop();
                std::cout << "YOU WON!" << std::endl;
            }
        }
                
        myscene.render();

        framecount++;

    });
}
