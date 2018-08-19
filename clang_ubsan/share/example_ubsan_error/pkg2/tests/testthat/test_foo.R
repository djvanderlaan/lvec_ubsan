library(testthat)

context("foo")

test_that("foo works", {


  a <- foobar(10)

  expect_equal(foo_get(a), 10)

})
