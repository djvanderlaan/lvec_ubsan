#ifndef pkg1_h
#define pkg1_h

#include <Rcpp.h>

// ==== VISITOR
/*template<typename T> class FooBar;

class FooBarVisitor {
  public:
    virtual void visit(FooBar<double>& vec) = 0;
    virtual void visit(FooBar<int>& vec) = 0;
};*/

// ==== FOO
class Foo {
  public:
    Foo() {};
    virtual ~Foo() {};

    //virtual void visit(FooBarVisitor* visitor) = 0;
};

// ==== FOOBAR
template<typename T>
class FooBar : public Foo {
  public:
    FooBar(T i = T()) : Foo(), i_(i) {};
    ~FooBar() {};

    T i() const { return i_;}
    void i(T i) { i_ = i;}

    //void visit(FooBarVisitor* visitor) {
      //visitor->visit(*this);
    //}


  private:
    T i_;
};

#endif
