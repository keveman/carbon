#include <exception>
#include <iostream>
#include <cxxabi.h>
#include <typeinfo>
#include <carbon/utility/intmap.hpp>
#include <carbon/lambda/expr.hpp>

using namespace std;

int main()
{
  // abi::__cxa_demangle(ti.name(), 0, 0, &status);
  using namespace carbon::utility;
  using namespace carbon::lambda;
  
  int t1=42;
  int t2=143;
  int t3=44;
  const int t4=0;
  int stat;
  cout << abi::__cxa_demangle(typeid(make_vector().operator()<int, int, int &, const int&>(t1,t2,t3,t4)).name(), 0, 0, &stat) << "\n";

  vector<intpair<0, int&>, vector<intpair<2, int&>, vector<intpair<42, int const&>, endmarker> > > mm =
    make_intmap<0, 2, 42, int&, int&, const int&>(t1, t2, t3);

  find_c<2>(mm).second++;
  intpair<2, int&> ans = find_c<2>(mm);

  cout << abi::__cxa_demangle(typeid(ans).name(), 0, 0, &stat) << "\n";

  cout << ans.second << "\n";
  cout << sizeof(make_vector().operator()<int,short,char>(0,0,0)) << "\n";
  cout << sizeof(mm) << "\n";

  cout << sizeof(2.0 / _1 + _2 + 1, _a) << "\n";
  2.0 / _1 + _2 + 1, _a[0], 1;
  _a = 1+34+_a, _3[
                   _a, _b = 3, _c=_d];

  cout << matches<expr<tag::add, int>, tag::add, _>::value << "\n";

  using namespace carbon::utility::debug;
  
  cout << "vector :" << append_vectors()(make_vector()(1,"teST"), make_vector()(2, "test2")) << "\n";
  return 0;
}
