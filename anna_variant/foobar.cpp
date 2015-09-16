#include <iostream>

struct S
{
  // explicit
  S(int) {}
};

void f(const S&)
{
  std::cout << "f called with an S" << std::endl;
}

int main()
{
  f(42);
}
