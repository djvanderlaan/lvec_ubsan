#include <Rcpp.h>
#include <pkg1.h>

// [[Rcpp::export]]
RcppExport int get_foobar(SEXP xp) {
  Rcpp::XPtr<Foo> x(xp);
  Foo* y1 = x;
  FooBar<int>* y2 = dynamic_cast<FooBar<int>*>(y1);
  return y2->i();
}

