#include "closest_dots.h"

template <typename T>
static T sqr(T elem) { return elem * elem; }

static long distance_sqr(const point_t& lhs, const point_t& rhs) noexcept {
    return sqr(static_cast<long>(rhs.first - lhs.first))
           + sqr(static_cast<long>(rhs.second - lhs.second));
}

static long near_line(std::vector<point_t> closests_to_line, long d_min_sqr) noexcept {
    auto min_sqr = d_min_sqr;

    for (int i = 0; i < static_cast<int>(closests_to_line.size()); ++i)
        for (int j = i+1;
             j < static_cast<int>(closests_to_line.size()) &&
             sqr(static_cast<long>(closests_to_line[j].second - closests_to_line[i].second)) < min_sqr; ++j)
            min_sqr = std::min(d_min_sqr, distance_sqr(closests_to_line[i], closests_to_line[j]));

    return min_sqr;
}

static long  closests_dots_impl(std::vector<point_t>& Xsorted, std::vector<point_t>& Ysorted) {
    // in recursion base case there is
    // brute force method.
    if (Xsorted.size() <= 3) {
        long min_distance = std::numeric_limits<long>::max();
        for (int  i = 0; i < static_cast<int>(Xsorted.size()); ++i)
            for (int j = i + 1; j < static_cast<int>(Xsorted.size()); ++j)
                min_distance = std::min(min_distance, distance_sqr(Xsorted[i], Xsorted[j]));
        return min_distance;
    }

    // dividing all point s in two area with
    // int middle
    std::vector<point_t> LeftXsorted(Xsorted.begin(), Xsorted.begin() + Xsorted.size()/2 + 1);
    std::vector<point_t> RightXsorted(Xsorted.begin() + Xsorted.size()/2 + 1, Xsorted.end());

    // middle point x coordinate;
    int middle = Xsorted[Xsorted.size()/2].first;

    std::vector<point_t> LeftYsorted , RightYsorted;
    LeftYsorted.reserve(LeftXsorted.size());
    RightYsorted.reserve(RightXsorted.size());

    for (auto& elem : Ysorted) {
        if (elem.first <= middle)
            LeftYsorted.push_back(elem);
        else
            RightYsorted.push_back(elem);
    }


    auto d_min_sqr = std::min(closests_dots_impl(LeftXsorted, LeftYsorted),
                              closests_dots_impl(RightXsorted, RightYsorted));

    // near_to_line checks all pairs made by dots in different areas
    // if they have distance sqr less than d_min_sqr
    // these possible variants placed in rectangle with size: x = 2*sqrt(d_min_sqr),
    // y = sqrt(d_min_sqr)
    // fact that near_line complexity is O(N), because named rectangle might contain only 8 points
    std::vector<point_t> closest_to_line;
    closest_to_line.reserve(Ysorted.size()/2);

    for (auto& elem : Ysorted)
        if (sqr(static_cast<long>(elem.first - middle)) < d_min_sqr)
            closest_to_line.push_back(elem);

    return std::min(d_min_sqr, near_line(std::move(Ysorted), d_min_sqr));
}

long closests_dots(std::vector<point_t> Xsorted) {
    std::vector<point_t> Ysorted(Xsorted);

    std::sort(Xsorted.begin(), Xsorted.end(),
              [] (point_t& lhs, point_t& rhs) { return lhs.first < rhs.first; });

    std::sort(Ysorted.begin(), Ysorted.end(),
              [] (point_t& lhs, point_t& rhs) { return lhs.second < rhs.second; });

    return closests_dots_impl(Xsorted, Ysorted);
}
