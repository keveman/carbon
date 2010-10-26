namespace carbon {

struct filler {};

namespace tag {
struct add {};
struct sub {};
struct mul {};
struct div {};
struct func {};
struct subscript {};
struct term {};
struct assign {};
struct comma {};
}

template<typename tag,
typename C0=filler,
typename C1=filler,
typename C2=filler,
typename C3=filler>
struct expr;

template<typename thetag,
typename C0,
typename C1,
typename C2,
typename C3>
struct expr {
  C0 c0;
  C1 c1;
  C2 c2;
  C3 c3;

  typedef struct { } isexpr;
  typedef expr<thetag, C0, C1, C2, C3> type;
};
}
