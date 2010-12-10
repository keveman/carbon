/*
 *  Copyright 2010-2012 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

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
