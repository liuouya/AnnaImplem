#include <type_traits>

// declaration only
template<typename T, typename... P0toN>
struct is_one_of;

// base #1: list is empty
template<typename T>
struct is_one_of<T> : std::false_type {};

// base #2: head of list is T
template<typename T, typename... P1toN>
struct is_one_of<T, T, P1toN...> : std::true_type {};

// general cases
template<typename T, typename P0, typename... P1toN>
struct is_one_of<T, P0, P1toN...> : is_one_of<T, P1toN...> {};


int main()
{
    static_assert(is_one_of<int, int>::value, "");
    static_assert(is_one_of<int, bool, int>::value, "");
    static_assert(is_one_of<int, int, int>::value, "");
    static_assert(!is_one_of<int, bool, char>::value, "");
}
