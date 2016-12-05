#include "shared_ptr.hpp"
#include <catch.hpp>

SCENARIO("Init", "[Init]"){
  shared_ptr<int> a;
  REQUIRE(a.count() == 0);
  REQUIRE(a.get() == nullptr);
}

SCENARIO("with parameteres", "[with param]"){
  shared_ptr<int> a(new int(5));
  REQUIRE(a.count() == 1);
  REQUIRE(*a == 5);
  }

SCENARIO("copy constructor", "[copy c]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b(a);
  REQUIRE(*b == 5);
  REQUIRE(b.count() == 2);
}

SCENARIO("copy operator", "[copy o]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b;
  b = a;
  REQUIRE(*b == 5);
  REQUIRE(b.count() == 2);
}

SCENARIO("move constructor", "[move c]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b(std::move(a));
  REQUIRE(*b == 5);
  REQUIRE(a.get() == nullptr);
  REQUIRE(b.count() == 1);
  REQUIRE(a.count() == 0);  
}

SCENARIO("move operator", "[move o]"){
  shared_ptr<int> a(new int(5));
  shared_ptr<int> b(new int(4));
  b = std::move(a);
  REQUIRE(*b == 5);
  REQUIRE(b.count() == 1);
  REQUIRE(a.get() == nullptr);
  REQUIRE(a.count() == 0);
}

SCENARIO("reset", "[reset]"){
  shared_ptr<int> a(new int(5));
  a.reset();
  REQUIRE(a.count() == 0);
  REQUIRE(a.get() == nullptr);
}
