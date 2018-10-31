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
    particle() : pos(new position()) {}

    particle(const particle& other)
        : pos(new position())
    {
        pos->x = other.pos->x;
        pos->y = other.pos->y;
        pos->z = other.pos->z;
    }

    ~particle() {delete pos;}

    position* pos;
};

int main()
{
    particle part1;
    part1.pos->x = 1.;

    particle part2{part1};
    part2.pos->x = 2.;

    auto pos1 = *(part1.pos);
    auto pos2 = *(part2.pos);

    assert(pos2.x != pos1.x);

    return 0;
}
