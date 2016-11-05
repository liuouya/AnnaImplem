#include <iostream>
#include <type_traits>
#include <utility>

template<class T>
struct Base {};

struct ImplOne : public Base<ImplOne>
{
    void print(std::ostream& os) const { os << "one";}
};

struct ImplTwo : public Base<ImplTwo>
{
    void print(std::ostream& os) const { os << "two";}
};

struct ImplThree : public Base<ImplThree>
{
    // print not implemented
};


// implement something to make this work
// cout << ImplOne() << ", "
//      << ImplTwo() << ", "
//      << ImplThree() << endl;
// and prints "one, two, "

template<class...>
using void_t = void;

template<class T>
struct is_printable
{
    static std::false_type try_print(...);

    template<class U, class = void_t<decltype(std::declval<U>().print(std::declval<std::ostream&>()))> >
    static std::true_type try_print(U&&);

public:
    using type = decltype(try_print(std::declval<T>()));
};

template<class T>
std::enable_if_t<is_printable<T>::type::value, std::ostream&> operator<<(std::ostream& lhs, const Base<T>& rhs)
{
    static_cast<const T&>(rhs).print(lhs);
    return lhs;
}

template<class T>
std::enable_if_t<!is_printable<T>::type::value, std::ostream&> operator<<(std::ostream& lhs, const Base<T>& rhs)
{
    return lhs;
}

int main() {

    // test
    static_assert(is_printable<ImplOne>::type::value, "");
    static_assert(!is_printable<ImplThree>::type::value, "");

    std::cout << ImplOne() << ", "
              << ImplTwo() << ", "
              << ImplThree()
              << std::endl;
}
