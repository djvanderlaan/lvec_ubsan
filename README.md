
Usage
-----------------------

Build Dockercontainer
```
./build.sh
```

Run container and open terminal on container (will mount directory `share`).
```
./run.sh
```

Type following commands:
```
cd /share
./test_all.sh
```

This builds and tests both packages. When testing `pkg2` the UBSAN warnings are generated (during installation of `pkg1` also a warning is generated which seems to be unrelated and not caused by the packages). 


Explanation of issue
-----------------------

One of my packges gives a message with the undefined behaviour sanitiser (UBSAN). I have difficulty tracking down/understanding the cause of this message. However, I have been able to create a small example that generates the same warning. The mail below is a bit on the long side, and, I hope it is readable as it mixes quite a lot code with text. I am sorry for that. A probably better readable version can be found at https://github.com/djvanderlaan/lvec_ubsan where also the complete source code and the docker image used for testing can be found. 

My example consists of two packages: pkg1 and pkg2. The package pkg2 links to pkg1. Package pkg1 defines a template class `FooBar<T>` which inherits from virtual class `Foo`. Pointers to the these objects are passed back to R using a `Rcpp:XPtr` object: 

    ========== pkg1/src/construct.cpp ================
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
    ========== END pkg1/src/construct.cpp ================

All headers of pkg1 are `inst/include`; these are included by `pkg2`: 

    ========== pkg1/inst/include/pkg1.h ================
    #include <Rcpp.h>
   
    // ==== VISITOR
    template<typename T> class FooBar;
   
    class FooBarVisitor {
      public:
        virtual void visit(FooBar<double>& vec) = 0;
        virtual void visit(FooBar<int>& vec) = 0;
    };
   
    // ==== FOO
    class Foo {
      public:
        Foo() {};
        virtual ~Foo() {};
   
        virtual void visit(FooBarVisitor* visitor) = 0;
    };

    // ==== FOOBAR
    template<typename T>
    class FooBar : public Foo {
      public:
        FooBar(T i = 0) : Foo(), i_(i) {};
        ~FooBar() {};
   
        T i() const { return i_;}
        void i(T i) { i_ = i;}
   
        void visit(FooBarVisitor* visitor) {
          visitor->visit(*this);
        }
      private:
        T i_;
    };
    #endif
    ========== END pkg1/inst/include/pkg1.h ================

The XPtr is passed to c++ code in pkg2 and methods of the Foo object are called:
 
    ========== pkg2/src/construct.cpp ================
    #include <Rcpp.h>
    #include <pkg1.h>

    // [[Rcpp::export]]
    RcppExport int get_foobar(SEXP xp) {
      Rcpp::XPtr<Foo> x(xp);
      Foo* y1 = x;
      FooBar<int>* y2 = dynamic_cast<FooBar<int>*>(y1);
      return y2->i();
    }
    ========== END pkg2/src/construct.cpp ================

This generates the following UBSAN messages:


    ========== WARNING MESSAGES ================
    Testing pkg2
    <U+221A> | OK F W S | Context
    / |  0       | fooconstruct.cpp:9:21: runtime error: <null> address 0x000003c21810 which does not point to an object of type 'Foo'
    0x000003c21810: note: object is of type 'FooBar<int>'
     00 00 00 00  58 1c 79 fd 48 7f 00 00  0a 00 00 00 00 00 00 00  20 00 00 00 00 00 00 00  01 03 00 00
                  ^~~~~~~~~~~~~~~~~~~~~~~
                  vptr for 'FooBar<int>'
    construct.cpp:10:14: runtime error: member call on address 0x000003c21810 which does not point to an object of type 'FooBar<int>'
    0x000003c21810: note: object is of type 'FooBar<int>'
     00 00 00 00  58 1c 79 fd 48 7f 00 00  0a 00 00 00 00 00 00 00  20 00 00 00 00 00 00 00  01 03 00 00
                  ^~~~~~~~~~~~~~~~~~~~~~~
                  vptr for 'FooBar<int>'
    /usr/local/lib/R/library/pkg1/include/pkg1.h:33:26: runtime error: member access within address 0x000003c21810 which does not point to an object of type 'const FooBar<int>'
    0x000003c21810: note: object is of type 'FooBar<int>'
     00 00 00 00  58 1c 79 fd 48 7f 00 00  0a 00 00 00 00 00 00 00  20 00 00 00 00 00 00 00  01 03 00 00
                  ^~~~~~~~~~~~~~~~~~~~~~~
                  vptr for 'FooBar<int>'
    <U+221A> |  1       | foo
    ========== END WARNING MESSAGES ================


I have had real problem reproducing this error. Also searching for the error give little clues as to what the problem is. The following message on the Rcpp-devel list seems somewhat similar: http://lists.r-forge.r-project.org/pipermail/rcpp-devel/2017-July/009656.html. I thought that it might be caused by the fact that I am passing pointers to template classes between libraries. I also couldn't find much about that. I did find some messages on passing pointers to STL objects between libraries. That should be ok, as long as the same compiler is used for both libraries. Although that might technically still make it undefined behaviour. 




