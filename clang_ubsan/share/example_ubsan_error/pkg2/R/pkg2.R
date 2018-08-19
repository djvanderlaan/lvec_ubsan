

#' @export
#' @useDynLib pkg2
#' @importFrom Rcpp sourceCpp
foo_get <- function(x) {
  get_foobar(x)
}
