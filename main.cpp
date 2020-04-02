#include <iostream>
#include <cassert>
#include "src/closest_dots.h"

int main() {
    int n = 0;
    std::cin >> n;

    assert(n >= 0);
    assert(std::cin.good());

    std::vector<point_t> points(n);

    for (auto& [first, second]: points) {
        std::cin >> first;
        assert(std::cin.good());
        std::cin >> second;
        assert(std::cin.good());
    }

    std::cout << closests_dots(std::move(points));

    return 0;
}