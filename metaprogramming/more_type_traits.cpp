#include <type_traits>
#include <utility>

// is_copy_assignable

template<class T>
struct is_copy_assignable
{
    // SFINAE may apply
    template<class U, class = decltype(std::declval<U&>() = std::declval<const U&>())>
    static std::true_type try_assignment(U&&);

    // catch all overload
    static std::false_type try_assignment(...);

public:
    using type = decltype(try_assignment(std::declval<T>()));
};

// void_t

template<class...>
using void_t = void;

// has_type_member

template<class, class = void>
struct has_type_member : std::false_type {};

template<class T>
struct has_type_member<T, void_t<typename T::type>> : std::true_type {};

int main()
{
    static_assert(has_type_member<std::remove_cv<int>>::value, "");
    static_assert(!has_type_member<int>::value, "");
}
