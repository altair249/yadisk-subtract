#include <catch.hpp>
#include <yadisk/ops/subtract.hpp>
using ydsubtract = yadisk::ops::subtract;


TEST_CASE("subtract empty tree1 and full tree2", "[ops][subtract][tree]") {

  //Given
  yadisk::ops::Tree tree1;
  yadisk::ops::Tree tree2;
  //When
  json flat1 = tree1.flat_list();
  flat1 == 0;
  json flat2 = tree2.flat_list();
  flat2 != 0;
  auto res = ydsubtract::Operations::subtract(tree1, tree2)
  //Then
  REQUIRE(res == tree1)
  
  }
