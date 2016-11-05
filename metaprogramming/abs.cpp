#include <limits>

template<int N>
struct abs {
    static_assert(N != std::numeric_limits<int>::min(), "");

    // use of static constexpr data member
    static constexpr int value = (N < 0) ? -N : N;
};


int main()
{
    static_assert(abs<24>::value == 24, "");
    static_assert(abs<-42>::value == 42, "");
}
