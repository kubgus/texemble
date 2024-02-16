#include <texemble.h>

#define WIDTH 12
#define HEIGHT 21

int main() {
    txm::scene<WIDTH, HEIGHT> myscene;

    txm::sprite wall = { WIDTH, 1, "]          [" };
    txm::sprite floor = { WIDTH, 1, "============" };

    txm::layer environment = &myscene;
    for (int i = 0; i < HEIGHT - 1; i++) environment.add(new txm::entity { 0, i, wall });
    txm::entity ground = { 0, HEIGHT - 1, floor };
    myscene.add(&ground);

    txm::sprite i_block = { 4, 1, "####" };
    txm::sprite j_block = { 3, 2, "#  ###" };
    txm::sprite l_block = { 3, 2, "  ####" };
    txm::sprite o_block = { 2, 2, "####" };
    txm::sprite s_block = { 3, 2, " #### " };
    txm::sprite t_block = { 3, 2, " # ###" };
    txm::sprite z_block = { 3, 2, "##  ##" };

    std::vector<const txm::sprite*> blocksheet = {
        &i_block,
        &j_block,
        &l_block,
        &o_block, 
        &s_block,
        &t_block,
        &z_block,
    };

    txm::layer blocks = &myscene;
    blocks.add(new txm::entity { WIDTH / 2, 0, *txm::random::element(blocksheet) });

    txm::input::handle([&](char in) {
        txm::entity* block = blocks.list().back();

        if (in == 'a' && block->x > 1) block->x--;
        if (in == 'd' && block->x < WIDTH - block->w() - 1) block->x++;
        
        if (in == 'q') block->s.rotate(txm::LEFT);
        if (in == 'e') block->s.rotate(txm::RIGHT);

        if (in == 'x') txm::gameloop::stop();
    });

    int difficulty = 240;

    int gravity = 6;

    int framecount = 0; 
    txm::gameloop::setframerate(24);
    txm::gameloop::start([&]() {
 
        myscene.clear();

        txm::entity* block = blocks.list().back();
        if (framecount % gravity == 0) block->y++;
        if (txm::collision::aabb(*block, ground)) {
            block->y--;
            blocks.add(new txm::entity { WIDTH / 2, 0, *txm::random::element(blocksheet) });
        }
        for (int j = 0; j < blocks.list().size(); j++) {
            txm::entity* other = blocks.list()[j];
            if (other == block) continue;
            if (txm::collision::charcol(*block, *other)) {
                block->y--;
                blocks.add(new txm::entity { WIDTH / 2, 0, *txm::random::element(blocksheet) });
            }
        }

        myscene.render();

        framecount++;

    });
}
