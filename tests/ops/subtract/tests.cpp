#include <catch.hpp>
#include <yadisk/ops/subtract.hpp>
using ydsubtract = yadisk::ops::subtract;


TEST_CASE("subtract empty tree1 and full tree2", "[ops][subtract][tree]") {

  //Given
  yadisk::ops::Tree tree1;
  yadisk::ops::Tree tree2;
  json flat1 = tree1.flat_list();
  json flat2 = tree2.flat_list();
    //When
  flat1 == 0;
  flat2 != 0;
  auto res = ydsubtract::Operations::subtract(tree1, tree2)
  //Then
  REQUIRE(res == tree1)
  
  }

TEST_CASE("subtract full tree1 and empty tree2", "[ops][subtract][tree]") {

  //Given
  yadisk::ops::Tree tree1;
  yadisk::ops::Tree tree2;
  json flat1 = tree1.flat_list();
  json flat2 = tree2.flat_list();
    //When
  flat1 != 0;
  flat2 == 0;
  auto res = ydsubtract::Operations::subtract(tree1, tree2)
  //Then
  REQUIRE(res == tree1)
  
  }

TEST_CASE("subtract empty tree1 and empty tree2", "[ops][subtract][tree]") {

  //Given
  yadisk::ops::Tree tree1;
  yadisk::ops::Tree tree2;
  json flat1 = tree1.flat_list();
  json flat2 = tree2.flat_list();
    //When
  flat1 == 0;
  flat2 == 0;
  auto res = ydsubtract::Operations::subtract(tree1, tree2)
  //Then
  REQUIRE(res == tree1)
  
  }

TEST_CASE("subtract full tree1 and full tree2", "[ops][subtract][tree]") {

  //Given
  yadisk::ops::Tree tree1;
  yadisk::ops::Tree tree2;
  json flat1 = tree1.flat_list();
  json flat2 = tree2.flat_list();
    //When
  flat1 != 0;
  flat2 != 0;
  auto res = ydsubtract::Operations::subtract(tree1, tree2)
  //Then
  REQUIRE(not res.empty())
  
  }
