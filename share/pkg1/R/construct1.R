.onLoad <- function(libname, pkgname) {
  library.dynam(pkgname, pkgname, libname, local=FALSE)
}

#' @importFrom Rcpp sourceCpp
#' @export
foobar <- function(x) {
  new_foobar(as.integer(x))
}

#' @export
foobard <- function(x) {
  new_foobard(as.double(x))
}


#' @export
foobar_get <- function(x) {
  get_foobar(x)
}


#' @export
foobard_get <- function(x) {
  get_foobard(x)
}
