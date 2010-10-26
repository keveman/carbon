#include <iostream>
#include <boost/proto/proto.hpp>
#include <boost/mpl/bool.hpp>
#include "carbon.hpp"

using namespace std;

namespace proto = boost::proto;
namespace mpl = boost::mpl;

template<typename>
struct foo_expr;

struct foo_grammar
  : proto::not_<proto::or_<
    proto::assign<foo_grammar, foo_grammar>
                , proto::plus_assign<foo_grammar, foo_grammar>
                , proto::minus_assign<foo_grammar, foo_grammar>
                , proto::multiplies_assign<foo_grammar, foo_grammar>
                , proto::divides_assign<foo_grammar, foo_grammar>
                , proto::modulus_assign<foo_grammar, foo_grammar>
                , proto::shift_left_assign<foo_grammar, foo_grammar>
                , proto::or_<
                  proto::shift_right_assign<foo_grammar, foo_grammar>                 
                , proto::bitwise_and_assign<foo_grammar, foo_grammar>
                , proto::bitwise_or_assign<foo_grammar, foo_grammar>
                , proto::bitwise_xor_assign<foo_grammar, foo_grammar> >                
> >
{};

struct foo_callable
  : proto::callable {

  template<typename>
  struct result;

  template<typename This, typename tag, typename LHS>
  struct result<This(tag, LHS)> {
    typedef carbon::expr<tag, LHS> type;
  };

  template<typename This, typename tag, typename LHS>
  struct result<This(tag, LHS&)> {
    typedef carbon::expr<tag, LHS> type;
  };

  template<typename This, typename tag, typename LHS, typename RHS>
  struct result<This(tag, LHS, RHS)> {
    typedef carbon::expr<tag, LHS, RHS> type;
  };
  /*
  template<typename tag, typename LHS>
  typename result<foo_callable(tag, LHS)>::type
  operator()(tag t, LHS l) {
    carbon::expr<tag, LHS> e = {l};
    return e;
  }
  */
  template<typename tag, typename LHS>
  typename result<foo_callable(tag, LHS&)>::type
  operator()(tag t, LHS &l) {
    carbon::expr<tag, LHS> e = {l};
    return e;
  }

  template<typename tag, typename LHS, typename RHS>
  typename result<foo_callable(tag, LHS, RHS)>::type
  operator()(tag t, LHS l, RHS r) {
    carbon::expr<tag, LHS, RHS> e = {l, r};
    return e;
  }

};

struct foo_transform
  : proto::or_<
    proto::when<proto::plus<foo_grammar, foo_grammar>,
    foo_callable(carbon::tag::add(), foo_transform(proto::_left), foo_transform(proto::_right))>
  , proto::when<proto::terminal<proto::_>,
    foo_callable(carbon::tag::term(), proto::_value)>
>
{};

struct foo_domain
  : proto::domain<proto::pod_generator<foo_expr>, foo_grammar>
{};

template<typename E>
struct foo_expr {
  BOOST_PROTO_BASIC_EXTENDS(E, foo_expr<E>, foo_domain)
};

struct foo {
  int id;
  foo(int _id) {
    cout << "foo default_constructor\n";
    id = _id;
  }
  
  foo(const foo &f) {
    id = f.id;
    cout << "foo copy_constructor\n";
  }
  
  template<typename E>
  void operator=(const E &e);  
};

template<typename LHS, typename RHS>
void printexpr(const carbon::expr<carbon::tag::add, LHS, RHS> &e)
{
  printexpr(e.c0);
  cout << " + ";
  printexpr(e.c1);
}

void printexpr(const carbon::expr<carbon::tag::term, foo> &e)
{
  cout << "foo" << e.c0.id;
}

template<typename E>
void foo::operator =(const E &e)
{
  printexpr(foo_transform()(e));
  //foo_transform()(e);
  cout << "\n";
  proto::display_expr(e);
}

template<typename>
struct is_foo : mpl::false_ {};

template<>
struct is_foo<foo> : mpl::true_ {};

namespace foo_ops {
BOOST_PROTO_DEFINE_OPERATORS(is_foo, foo_domain)
}

int main()
{
  using namespace foo_ops;
  foo a(1), b(2);
  a=a+b;
  return 0;
}
