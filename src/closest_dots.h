#pragma once

#include <vector>
#include <algorithm>
#include <limits>

using point_t = std::pair<int, int>;
// complextiy O(n*log(n))
long closests_dots(std::vector<point_t>);

