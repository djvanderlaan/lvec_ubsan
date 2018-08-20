library(testthat)

context("foo")

test_that("foo works", {


  a <- foobar(10)

  expect_equal(foobar_get(a), 10)

  b <- foobard(1.0)

  expect_equal(foobard_get(b), 1.0)

})
