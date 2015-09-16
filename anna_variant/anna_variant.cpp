#include <boost/variant.hpp>
#include <string>
#include <iostream>
#include "mafan_struct.hpp"

namespace anna {
  
  template<typename Base, typename... Other>
  class		variant
  {
  public:
    char	value_[sizeof(variant<Other...>) > sizeof(Base) ?
		       sizeof(variant<Other...>) : sizeof(Base)];
    bool	is_base_;

    // ctor
    variant(const Base& value)
      : value_(), is_base_(true)
    {
      new(&value_) Base(value);
    }

    template<typename T>
    variant(const T& t)
      : value_(), is_base_(false)
    {
      new(&value_) variant<Other...>(t);
    }

    // dtor
    void free()
    {
      if (is_base_)
	reinterpret_cast<Base*>(&value_)->~Base();
      else
	reinterpret_cast<variant<Other...>*>(&value_)->~variant<Other...>();
    }
    
    ~variant()
    {
      free();
    }

    // operator=
    variant& operator=(const Base& value)
    {
      free();
      new(&value_) Base(value);
      is_base_ = true;
      return *this;
    }

    template<typename T>
    variant& operator=(const T& value)
    {
      free();
      new(&value_) variant<Other...>(value);
      is_base_ =false;
      return *this;
    }
    
  };

  template<typename Base>
  class		variant<Base>
  {
  public:
    char	value_[sizeof(Base)];

    variant(const Base& value)
      : value_()
    {
      new(&value_) Base(value);
    }

    ~variant()
    {
      reinterpret_cast<Base*>(value_)->~Base();
    }
    
    variant& operator=(const Base& value)
    {
      reinterpret_cast<Base*>(value_)->~Base();
      new(&value_) Base(value);
      return *this;
    }
    
  };

}

template<typename Base, typename... Other>
std::ostream& operator<<(std::ostream& os, const anna::variant<Base, Other...>& v)
{
  if (v.is_base_)
    return os << *reinterpret_cast<const Base*>(v.value_);
  return os << *reinterpret_cast<const anna::variant<Other...>*>(v.value_);
}

template<typename Base>
std::ostream& operator<<(std::ostream& os, const anna::variant<Base>& v)
{
  return os << *reinterpret_cast<const Base*>(v.value_);
}

using namespace anna;
// using namespace boost;

int main()
{
  // S s;
  
  variant<std::string, int, double> v(std::string("hello world"));
  std::cout << v << std::endl;

  variant<int, double, std::string> v2(std::string("hello world"));
  std::cout << v2 << std::endl;

  variant<const char*, int, double> v3("hello world");
  std::cout << v3 << std::endl;

  variant<int, double, const char*> v4("hello world");
  std::cout << v4 << std::endl;

  v = 3;
  std::cout << v << std::endl;
  v = 42.24;
  std::cout << v << std::endl;

  // boost::variant<const char*, std::string> v3("hello world");
  // std::cout << boost::get<std::string>(&v3) << std::endl;
  // std::cout << boost::get<const char *>(&v3) << std::endl;

  // v3 = std::string("hey");
  // std::cout << boost::get<std::string>(&v3) << std::endl;
  // std::cout << boost::get<const char *>(&v3) << std::endl;

}
