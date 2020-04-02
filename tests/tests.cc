#include <gtest/gtest.h>
#include "../src/closest_dots.h"

long BruteForce(std::vector<point_t>& points) noexcept {
    auto distance_sqr = [] (const point_t& lhs, const point_t& rhs) -> long
    {
        return static_cast<long>(rhs.first - lhs.first) * static_cast<long>(rhs.first - lhs.first)
               + static_cast<long>(rhs.second - lhs.second) * static_cast<long>(rhs.second - lhs.second);
    };

    auto min = std::numeric_limits<long>::max();
    for (int i = 0; i < static_cast<int>(points.size()); ++i)
        for (int j = i+1; j < static_cast<int>(points.size()); ++j)
            min = std::min(min, distance_sqr(points[i], points[j]));

    return min;
}

class generator final {
public:
     enum class MODE {
        RAND_GENERATE,
        SAME_X,
        SAME_Y
    };
private:
    int limit_;
    MODE mode_;
    int same_value_;
public:

    explicit generator(int limit, MODE mode = MODE::RAND_GENERATE, int same_value = 0)
        :
        limit_(limit),
        mode_(mode),
        same_value_(same_value)
    {
        std::srand(std::time(nullptr));
    }

    point_t operator() () const noexcept {
        switch (mode_) {
            case MODE::RAND_GENERATE: {
                int x = std::rand() % (2 * limit_) + 1 - limit_;
                int y = std::rand() % (2 * limit_) + 1 - limit_;
                return std::make_pair(x, y);
            }

            case MODE::SAME_X: {
                int y = std::rand() % (2 * limit_) + 1 - limit_;
                return std::make_pair(same_value_, y);
            }

            case MODE::SAME_Y: {
                int x = std::rand() % (2 * limit_) + 1 - limit_;
                return std::make_pair(x, same_value_);
            }
        }
    }
};


TEST(closest_dots, big_data) {
    std::vector<point_t> points(100000);
    std::generate(points.begin(), points.end(), generator{10000});
    ASSERT_EQ(BruteForce(points), closests_dots(std::move(points)));
}


TEST(closest_dots, tests) {
    std::vector<point_t> points(10000);

    std::generate(points.begin(), points.end(), generator{100000});
    ASSERT_EQ(BruteForce(points), closests_dots(points));

    std::generate(points.begin(), points.end(), generator{100000, generator::MODE::SAME_X, 0});
    ASSERT_EQ(BruteForce(points), closests_dots(points));

    std::generate(points.begin(), points.end(), generator{100000, generator::MODE::SAME_Y, 0});
    ASSERT_EQ(BruteForce(points), closests_dots(points));
}

int main (int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return ::RUN_ALL_TESTS();
}