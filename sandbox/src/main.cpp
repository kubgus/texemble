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

template <int width, int height>
void remove(int index, txm::entity* ent, std::vector<txm::entity*>& list, txm::scene<width, height>& scene) {
    if (scene.contains(ent)) scene.remove(ent);
    list.erase(list.begin() + index);
    delete ent;
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

    std::vector<txm::entity*> projectiles;
    std::vector<txm::entity*> enemies;

    txm::input::handle([&](char in) {
        if (in == 'w') player.y--;
        if (in == 's') player.y++;
        if (in == 'a') player.x--;
        if (in == 'd') player.x++;

        if (in == ' ') projectiles.push_back(new txm::entity { player.x + 2, player.y, bullet});

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
            enemies.push_back(new txm::entity { random(0, WIDTH - 1), 0, asteroid });

        for (int i = 0; i < projectiles.size(); i++) {
            txm::entity* projectile = projectiles[i];
            if (!myscene.contains(projectile)) myscene.add(projectile);
            projectile->y--;

            if (projectile->y <= 0) {
                remove(i, projectile, projectiles, myscene);
                continue;
            }
        }

        for (int i = 0; i < enemies.size(); i++) {
            txm::entity* enemy = enemies[i];
            if (!myscene.contains(enemy)) myscene.add(enemy);
            if (framecount % 4 == 0) enemy->y++;

            if (enemy->y > HEIGHT - 2) {
                score--;
                remove(i, enemy, enemies, myscene);
            }

            for (txm::entity* projectile : projectiles) {
                if (txm::collision::aabb(*projectile, *enemy)) {
                    score++;
                    remove(i, enemy, enemies, myscene);
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
