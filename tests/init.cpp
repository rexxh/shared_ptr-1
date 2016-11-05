#include "sharedptr.hpp"
#include <catch.hpp>

SCENARIO("Init", "[Init]"){
  shared_ptr<int> a;
  REQUIRE(a.use_count() == 0);
}
