#include "../inst/include/pkg1.h"

// [[Rcpp::export]]
SEXP new_foobar(int i) {
  FooBar<int>* x = new FooBar<int>(i);
  return Rcpp::XPtr<Foo>(x, true);
}

// [[Rcpp::export]]
SEXP new_foobard(double i) {
  FooBar<double>* x = new FooBar<double>(i);
  return Rcpp::XPtr<Foo>(x, true);
}


// [[Rcpp::export]]
RcppExport int get_foobar(SEXP xp) {
  Rcpp::XPtr<Foo> x(xp);
  Foo* y1 = x;
  FooBar<int>* y2 = dynamic_cast<FooBar<int>*>(y1);
  return y2->i();
}

//RcppExport int get_foobar(Rcpp::XPtr<Foo> x) {
  //Foo* y1 = x;
  //FooBar<int>* y = dynamic_cast<FooBar<int>*>(y1);
  //return y->i();
//}


// [[Rcpp::export]]
RcppExport double get_foobard(Rcpp::XPtr<Foo> x) {
  Foo* y1 = x;
  FooBar<double>* y = dynamic_cast<FooBar<double>*>(y1);
  return y->i();
}

