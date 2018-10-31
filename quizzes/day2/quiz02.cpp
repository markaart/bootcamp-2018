#include <cassert>

struct position
{
    explicit position(double x = 0., double y = 0., double z = 0.)
        : x(x), y(y), z(z)
    {}

    double x;
    double y;
    double z;
};

struct particle
{
    particle(position* pos = new position())
        : pos(pos)
    {}

    position* pos;
};

int main()
{
    particle part3;
    part3.pos->x = 1.;

    position pos1{1., 0., -1.};

    particle part1{&pos1};
    particle part2{part1};
    part2.pos->x = 2.;

    auto pos2 = *(part2.pos);
    assert(pos2.x != pos1.x);

    return 0;
}
