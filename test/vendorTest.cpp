#include <gtest/gtest.h>
#include "../src/vendor.h"
#include <memory>
#include <iostream>
#include <stdexcept>

using namespace AutoVendor;

class VendorTest : public ::testing::Test {

protected:

  std::unique_ptr<Vendor> vendor;

  VendorTest() {vendor = std::unique_ptr<Vendor>(new Vendor());}

  virtual void SetUp() { std::cout << "run SetUp()" << std::endl; }
  virtual void TearDown() { std::cout << "run TearDown()" << std::endl; }
};

// Test Vendor.input()
TEST_F(VendorTest, Input1000) {
  vendor->input(Money::Thousand);
  EXPECT_EQ(1000u, vendor->getSum());
}

TEST_F(VendorTest, Input500) {
  vendor->input(Money::FiveHundored);
  EXPECT_EQ(500u, vendor->getSum());
}

TEST_F(VendorTest, Input100) {
  vendor->input(Money::Hundored);
  EXPECT_EQ(100u, vendor->getSum());
}

TEST_F(VendorTest, Input50) {
  vendor->input(Money::Fifty);
  EXPECT_EQ(50u, vendor->getSum());
}

TEST_F(VendorTest, Input10) {
  vendor->input(Money::Ten);
  EXPECT_EQ(10u, vendor->getSum());
}

TEST_F(VendorTest, Input) {
  vendor->input(Money::Hundored);
  vendor->input(Money::Ten);
  EXPECT_EQ(110u, vendor->getSum());
  vendor->input(Money::Thousand);
  EXPECT_EQ(1110u, vendor->getSum());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
