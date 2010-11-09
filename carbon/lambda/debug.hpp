#pragma once
#include <carbon/lambda/expr.hpp>
#include <iostream>

namespace carbon { namespace lambda {
namespace debug {

template<typename TERM>
void printexpr(const expr<tag::term, TERM> &e)
{
  std::cerr << e.c0;
}

template<int N>
void printexpr(const expr<tag::term, arg<N> >&)
{
  std::cerr << "arg" << N;
}

template<int N>
void printexpr(const expr<tag::term, localvar<N> >&)
{
  std::cerr << "_" << (char)('a'+N);
}

#define PRINT_BIN_EXPR_DECL(TAG)                \
template<typename LHS, typename RHS>            \
 void printexpr(const expr<TAG, LHS, RHS> &e);
PRINT_BIN_EXPR_DECL(tag::mul) 
PRINT_BIN_EXPR_DECL(tag::div) 
PRINT_BIN_EXPR_DECL(tag::comma)
PRINT_BIN_EXPR_DECL(tag::assign)
PRINT_BIN_EXPR_DECL(tag::add) 
PRINT_BIN_EXPR_DECL(tag::sub) 
#undef PRINT_BIN_EXPR_DECL
template<typename LHS, typename RHS>
void printexpr(const expr<tag::subscript, LHS, RHS> &e);
template<typename RHS>
void printexpr(const expr<tag::iftag, RHS> &e);

#define PRINT_BIN_EXPR(TAG, OP)                 \
template<typename LHS, typename RHS>            \
 void printexpr(const expr<TAG, LHS, RHS> &e)   \
{                                               \
  printexpr(e.c0);                              \
  std::cerr << " " << OP << " ";                \
  printexpr(e.c1);                              \
}
PRINT_BIN_EXPR(tag::mul, "*")
PRINT_BIN_EXPR(tag::div, "/")
PRINT_BIN_EXPR(tag::comma, ",")
PRINT_BIN_EXPR(tag::assign, "=")
PRINT_BIN_EXPR(tag::add, "+")
PRINT_BIN_EXPR(tag::sub, "-")

#undef PRINT_BIN_EXPR

template<typename LHS, typename RHS>
void printexpr(const expr<tag::subscript, LHS, RHS> &e)
{
  printexpr(e.c0);
  std::cerr << "[";
  printexpr(e.c1);
  std::cerr << "]";
}

template<typename RHS>
void printexpr(const expr<tag::iftag, RHS> &e)
{
  std::cerr << "if(";
  printexpr(e.c0);
  std::cerr << ")";
}

}
} }
