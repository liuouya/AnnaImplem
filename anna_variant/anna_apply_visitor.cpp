#include <boost/variant.hpp>
#include <iostream>
#include <string>

namespace anna {

  // static_visitor
  template<typename T = void>
  class	static_visitor
  {
  public:
    typedef T result_type;
  };

  // variant
  template<typename Base, typename... Other>
  class		variant
  {
  public:
    char	value_[sizeof(variant<Other...>) > sizeof(Base) ?
		       sizeof(variant<Other...>) : sizeof(Base)];
    bool	is_base_;
    
    // ctor
    variant(const Base& value = Base())
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
      if (is_base_)
      {
	(*reinterpret_cast<Base*>(&value_)) = value;
      }
      else
      {
	reinterpret_cast<variant<Other...>*>(&value_)->~variant<Other...>();
	new(&value_) Base(value);
	is_base_ = true;
      }
      return *this;
    }

    template<typename T>
    variant& operator=(const T& value)
    {
      free();
      new(&value_) variant<Other...>(value);
      is_base_ = false;
      return *this;
    }
    
    // operator()
    template<typename T>
    void operator()(T& visitor)
    {
      if (is_base_)
	visitor(*reinterpret_cast<Base*>(&value_));
      else
	(*reinterpret_cast<variant<Other...>*>(&value_))(visitor);
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
    }

    template<typename T>
    void operator()(T& visitor)
    {
      visitor(value_);
    }

  };

  // apply_visitor
  template<typename T, typename... U>
  void	apply_visitor(T& visitor, variant<U...> v)
  {
    v(visitor);
  }

}

// operator<< overload

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

// simple unit test

// using namespace boost;
using namespace anna;

struct Output : public static_visitor<>
{
  result_type operator()(const double& d) const { std::cout << d << '\n'; }
  result_type operator()(char c) const { std::cout << c << '\n'; }
  result_type operator() (const char* s) const { std::cout << "cstring: " << s << std::endl; }
  result_type operator()(const std::string& s) const { std::cout << "std::string: " << s << '\n'; }
};

int	main()
{
  variant<int, double, std::string> v2("a string");
  std::cout << "v2: " << v2 << std::endl;

  variant<std::string, const char*, char> v1("Boost");
  std::cout << "v1: " << v1 << std::endl;

  variant<double, char, std::string, const char*> v("a string");
  std::cout << "v: " << v1 << std::endl;

  Output O;
  apply_visitor(O, v);
  v = 3.14;
  apply_visitor(O, v);
  v = 'A';
  apply_visitor(O, v);

  const char* cstring = "Boost";
  v = cstring;
  apply_visitor(O, v);
}
