// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/pkg1.h"
#include <Rcpp.h>

using namespace Rcpp;

// new_foobar
SEXP new_foobar(int i);
RcppExport SEXP _pkg1_new_foobar(SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< int >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(new_foobar(i));
    return rcpp_result_gen;
END_RCPP
}
// new_foobard
SEXP new_foobard(double i);
RcppExport SEXP _pkg1_new_foobard(SEXP iSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< double >::type i(iSEXP);
    rcpp_result_gen = Rcpp::wrap(new_foobard(i));
    return rcpp_result_gen;
END_RCPP
}
// get_foobar
RcppExport int get_foobar(SEXP xp);
RcppExport SEXP _pkg1_get_foobar(SEXP xpSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< SEXP >::type xp(xpSEXP);
    rcpp_result_gen = Rcpp::wrap(get_foobar(xp));
    return rcpp_result_gen;
END_RCPP
}
// get_foobard
RcppExport double get_foobard(Rcpp::XPtr<Foo> x);
RcppExport SEXP _pkg1_get_foobard(SEXP xSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<Foo> >::type x(xSEXP);
    rcpp_result_gen = Rcpp::wrap(get_foobard(x));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_pkg1_new_foobar", (DL_FUNC) &_pkg1_new_foobar, 1},
    {"_pkg1_new_foobard", (DL_FUNC) &_pkg1_new_foobard, 1},
    {"_pkg1_get_foobar", (DL_FUNC) &_pkg1_get_foobar, 1},
    {"_pkg1_get_foobard", (DL_FUNC) &_pkg1_get_foobard, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_pkg1(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
