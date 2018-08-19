#include "../inst/include/pkg1.h"


// [[Rcpp::export]]
RcppExport SEXP new_foobar(int i) {
  BEGIN_RCPP
  FooBar<int>* x = new FooBar<int>(i);
  return Rcpp::XPtr<Foo>(x, true);
  END_RCPP
}

// [[Rcpp::export]]
RcppExport SEXP new_foobard(double i) {
  BEGIN_RCPP
  FooBar<double>* x = new FooBar<double>(i);
  return Rcpp::XPtr<Foo>(x, true);
  END_RCPP
}


// [[Rcpp::export]]
RcppExport int get_foobar(Rcpp::XPtr<Foo> x) {
  Foo* y1 = x;
  FooBar<int>* y = dynamic_cast<FooBar<int>*>(y1);
  return y->i();
}


// [[Rcpp::export]]
RcppExport double get_foobard(Rcpp::XPtr<Foo> x) {
  Foo* y1 = x;
  FooBar<double>* y = dynamic_cast<FooBar<double>*>(y1);
  return y->i();
}

