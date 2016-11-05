#include <type_traits>
#include <cstdint>

// remove_const

template<typename T>
struct remove_const
{
    using type = T;
};

template<typename U>
struct remove_const<const U>
{
    using type = U;
};

// type_is

template<typename T>
struct type_is
{
    using type = T;
};

// remove_volatile

template<typename T>
struct remove_volatile : type_is<T> {};

template<typename U>
struct remove_volatile<volatile U> : type_is<U> {};

// IF (std::conditional)

template<bool, typename T, typename>
struct IF : type_is<T> {};

template<typename T, typename F>
struct IF<false, T, F> : type_is<F> {};

// enable_if

template<bool, typename T>
struct enable_if : type_is<T> {};

template<typename U>
struct enable_if<false, U> {};

// SFINAE in use

template<typename T>
enable_if<std::is_integral<T>::value, intmax_t> f(T val) { return 0; }

template<typename T>
enable_if<std::is_floating_point<T>::value, long double> f(T val) { return 0; }

// integral_constant (canonical C++11 value returning metafunction)

template<typename T, T v>
struct integral_constant
{
    static constexpr T value = v;
    constexpr operator T() const noexcept { return value; }
    constexpr T operator()() const noexcept { return value; }
    // ...
};

// bool_constant, true_type, false_type

template<bool b>
using bool_constant = integral_constant<bool, b>;

using true_type = bool_constant<true>;
using false_type = bool_constant<false>;

// is_same

template<typename T, typename U>
struct is_same : false_type {};

template<typename T>
struct is_same<T, T> : true_type {};

// remove_cv

template<typename T>
using remove_cv = remove_volatile<typename remove_const<T>::type>;

// is_void

template<typename T>
struct is_void : is_same<void, typename remove_cv<T>::type> {};


int main()
{
    static_assert(std::is_same<int, remove_const<const int>::type>::value, "");
    static_assert(std::is_same<char[42], remove_const<const char[42]>::type>::value, "");

    static_assert(std::is_same<int, remove_volatile<volatile int>::type>::value, "");
    static_assert(std::is_same<char[42], remove_volatile<volatile char[42]>::type>::value, "");

    static_assert(std::is_same<int, IF<true, int, char>::type>::value, "");
    static_assert(std::is_same<char, IF<false, int, char>::type>::value, "");

    static_assert(is_void<const void>::value, "");
    static_assert(!is_void<const void*>::value, "");
}
