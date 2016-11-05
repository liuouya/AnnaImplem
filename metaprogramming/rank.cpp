#include <stdlib.h>

// primary template

template<typename T>
struct rank
{
    static constexpr size_t value = 0u;
};

// specialization (recursion)

template<typename U, size_t N>
struct rank<U[N]>
{
    static constexpr size_t value = 1 + rank<U>::value;
};

int main()
{
    using array_t = int[10][20][30];
    static_assert(rank<array_t>::value == 3, "");
}
