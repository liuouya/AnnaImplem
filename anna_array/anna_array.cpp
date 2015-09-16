#include <iostream>
#include <array>

namespace	anna
{
  template<typename T, std::size_t N>
  struct array
  {
    T value_[N];

    T& operator[](std::size_t pos)
    {
      return value_[pos];
    }

    class iterator
    {
      T* it_;

    public:

      iterator(T* it)
	: it_(it)
      {
      }
      
      iterator& operator++()
      {
	++it_;
	return *this;
      }

      T& operator*()
      {
	return *it_;
      }

      bool operator!=(const iterator& other)
      {
	return it_ != other.it_;
      }
      
    };

    iterator begin()
    {
      return iterator(&value_[0]);
    }

    iterator end()
    {
      return iterator(&value_[N]);
    }

  };



};

// anna::array test

int	main()
{
  anna::array<int, 3> a1{ {1, 2, 3} };
  if (a1[0] != 1)
    std::cerr << "failed to get the correct value for a1[0]" << std::endl;
  
  anna::array<char, 4> a2 = {'a', 'b', 'c'};
  if (a2[1] != 'b')
    std::cerr << "failed to get the correct value for a2[1]" << std::endl;

  anna::array<std::string, 3> a3 = { std::string("a"), "b", "yoohoo" };
  if (a3[2] != "yoohoo")
    std::cerr << "failed to get the correct value for a3[2]" << std::endl;

  anna::array<int, 5> sa1{ {1, 2, 3, 4, 5} };
  anna::array<int, 5>::iterator ait = sa1.begin();
  anna::array<int, 5>::iterator ait_end = sa1.end();
  for (; ait != ait_end; ++ait)
    {
      std::cout << *ait << std::endl;
    }

  // ranged for loop
  // for(const auto& s: a3)
  //   std::cout << s << ' ';
}
