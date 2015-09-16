
template <int U, int... I>
struct maximum_from_int_list
{
  static const int value = U >= maximum_from_int_list<I...>::value ?
    U : maximum_from_int_list<I...>::value;
};

template<int I>
struct maximum_from_int_list<I>
{
  static const int value = I;  
};
  
int main()
{
  static_assert(maximum_from_int_list<1, -5, 42, 3, 6>::value == 42,
		"Failed to get maximum_from_int_list");
  static_assert(maximum_from_int_list<1>::value == 1,
		"Failed to get maximum_from_int_list");
}
