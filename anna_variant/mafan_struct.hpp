#ifndef MAFAN_STRUCT_HPP
#define MAFAN_STRUCT_HPP

#include <iosfwd>

struct S
{
private:
    S& operator=(const S&);
};

std::ostream& operator<<(std::ostream& os, const S&)
{
  return os;
}

#endif // MAFAN_STRUCT_HPP
