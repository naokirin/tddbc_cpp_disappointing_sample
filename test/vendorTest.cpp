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


// Test Vendor.inventory
TEST_F(VendorTest, coke) {
  auto inventory = vendor->getInventory();
  ASSERT_EQ(1u, inventory.size());
  EXPECT_EQ(1u, inventory[1u].id);
  EXPECT_EQ("coke", inventory[1u].name);
  EXPECT_EQ(5u, inventory[1u].num);
  EXPECT_EQ(120u, inventory[1u].value);
}

TEST_F(VendorTest, addStock) {
  vendor->addStock({2u, "", 0u, 0u});
  auto inventory = vendor->getInventory();
  ASSERT_EQ(2u, inventory.size());
  EXPECT_EQ(2u, inventory[2u].id);
  EXPECT_EQ("", inventory[2u].name);
  EXPECT_EQ(0u, inventory[2u].num);
  EXPECT_EQ(0u, inventory[2u].value);
}


// vendor.purchase
TEST_F(VendorTest, purchasable) {
  vendor->input(Money::Hundored);
  vendor->input(Money::Fifty);
  ASSERT_EQ(1u, vendor->getPurchasableList().size());
  EXPECT_EQ(1u, vendor->getPurchasableList().front());
}

TEST_F(VendorTest, notPurchasable) {
  vendor->input(Money::Hundored);
  EXPECT_TRUE(vendor->getPurchasableList().empty());
}

TEST_F(VendorTest, purchase) {
  vendor->input(Money::Thousand);
  vendor->purchase(1u);
  auto inventory = vendor->getInventory();
  EXPECT_EQ(4u, inventory[1u].num);
  EXPECT_EQ(880u, vendor->getSum());
}

TEST_F(VendorTest, notPurchase) {
  vendor->input(Money::Hundored);
  vendor->purchase(1u);
  auto inventory = vendor->getInventory();
  EXPECT_EQ(5u, inventory[1].num);
  EXPECT_EQ(100u, vendor->getSum());
}

TEST_F(VendorTest, sales) {
  vendor->input(Money::Thousand);
  EXPECT_EQ(0u, vendor->getSales());
  vendor->purchase(1u);
  EXPECT_EQ(120u, vendor->getSales());
  vendor->purchase(1u);
  EXPECT_EQ(240u, vendor->getSales());
}

TEST_F(VendorTest, nothingInventory) {
  vendor->input(Money::Thousand);
  vendor->purchase(1u); vendor->purchase(1u); vendor->purchase(1u); vendor->purchase(1u); vendor->purchase(1u);
  EXPECT_EQ(400u, vendor->getSum());
  EXPECT_EQ(600u, vendor->getSales());
  vendor->purchase(1u);
  EXPECT_EQ(400u, vendor->getSum());
  EXPECT_EQ(600u, vendor->getSales());
}



int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
