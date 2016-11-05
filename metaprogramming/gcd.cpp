// primary template (recursion)

template<unsigned M, unsigned N>
struct gcd {
    static constexpr int value = gcd<N, M%N>::value; // per Euclid
};

// specialization

template<unsigned M>
struct gcd<M, 0> {
    static_assert(M != 0, "");
    static const int value = M;
};

int main()
{
    static_assert(gcd<3, 2>::value == 1, "");
    static_assert(gcd<4, 2>::value == 2, "");
    static_assert(gcd<12, 15>::value == 3, "");
}
