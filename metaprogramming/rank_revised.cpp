#include <stdlib.h>
#include <type_traits>

// alternative implementation with integral_constant

// primary template

template<typename T>
struct rank : std::integral_constant<size_t, 0u> {};

// specialization (recursion)

template<typename U, size_t N>
struct rank<U[N]> : std::integral_constant<size_t, rank<U>::value + 1 > {};

// specialization (unbounded array type)

template<typename U>
struct rank<U[]> : std::integral_constant<size_t, rank<U>::value + 1 > {};


int main()
{
    using array_t = int[10][20][30];
    static_assert(rank<array_t>::value == 3, "");

    static_assert(rank<int[][20][30]>::value == 3, "");
}
