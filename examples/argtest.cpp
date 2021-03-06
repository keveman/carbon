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

#include <iostream>
#include <carbon/lambda/primitives.hpp>
#include <carbon/lambda/operators.hpp>
#include <carbon/lambda/statements.hpp>
#include <carbon/lambda/functions.hpp>

using namespace std;
using namespace carbon::lambda;

struct fact_impl {

  template<typename Arg>
  struct result {
    typedef Arg type;
  };

  template<typename Arg>
  Arg operator()(Arg n) const {
    return (n <= 0) ? 1 : n * this->operator()(n-1);
  }
};

function<fact_impl> const factorial;

template<typename F>
void foo(F f)
{
  int i=42;
  f(i,10);
  cout << i << "\n";
}

int main()
{
  __typeof__((factorial(arg1))) prog = (factorial(arg1));
  //foo((arg1=factorial(arg2)));
  foo(arg1=prog(10));

  vector_type<int>::type a = make_vector().operator()<int>(2);

  vector_type<intpair<1, int> >::type b = make_vector()(intpair<1, int>(42));

  cout << _b.eval(append_vectors()(a,b)) << "\n";
  
  bool jj;
  let_(_a=_1)[
    let_(_b=42)[
      if_(_a == _b) [
        _2 = true
      ].else_[
        _2 = false
      ]
    ]  
  ](42, jj);
  cout << jj << "\n";

  int i=0, j=41;

  let_(_a=_2) [
    while_(_a >= 0) [
      _1 = _1 + 1,
      _a = _a-1
    ]
  ] (i, j);
  
  cout << i << "\n";

  cout << (let_(_a=i)[_a=256])(0) << "\n";

  cout << (_1+_2+_3)(0, 41, 1) << "\n";

  i=0;
  cout << (let_(_a = _1)[_4 = _a+_2+_3])(1,2,3,i) << "\n";
  cout << i << "\n";

  return 0;
}
