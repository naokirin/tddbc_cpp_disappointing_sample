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

  virtual void SetUp() {}
  virtual void TearDown() {}
};

// Test Vendor.input()
TEST_F(VendorTest, Input1000) {
  vendor->input(Money::Thousand);
  EXPECT_EQ(1000u, vendor->getTotalAmount());
}

TEST_F(VendorTest, Input500) {
  vendor->input(Money::FiveHundored);
  EXPECT_EQ(500u, vendor->getTotalAmount());
}

TEST_F(VendorTest, Input100) {
  vendor->input(Money::Hundored);
  EXPECT_EQ(100u, vendor->getTotalAmount());
}

TEST_F(VendorTest, Input50) {
  vendor->input(Money::Fifty);
  EXPECT_EQ(50u, vendor->getTotalAmount());
}

TEST_F(VendorTest, Input10) {
  vendor->input(Money::Ten);
  EXPECT_EQ(10u, vendor->getTotalAmount());
}

TEST_F(VendorTest, Input) {
  vendor->input(Money::Hundored);
  vendor->input(Money::Ten);
  EXPECT_EQ(110u, vendor->getTotalAmount());
  vendor->input(Money::Thousand);
  EXPECT_EQ(1110u, vendor->getTotalAmount());
}


// Test Vendor.inventory
TEST_F(VendorTest, coke) {
  auto inventory = vendor->getInventory();
  ASSERT_EQ(3u, inventory.size());
  EXPECT_EQ(1u, inventory[1u].id);
  EXPECT_EQ("コーラ", inventory[1u].name);
  EXPECT_EQ(5u, inventory[1u].num);
  EXPECT_EQ(120u, inventory[1u].value);
}

TEST_F(VendorTest, addStock) {
  vendor->addStock({10u, "", 0u, 0u});
  auto inventory = vendor->getInventory();
  ASSERT_EQ(4u, inventory.size());
  EXPECT_EQ(10u, inventory[10u].id);
  EXPECT_EQ("", inventory[10u].name);
  EXPECT_EQ(0u, inventory[10u].num);
  EXPECT_EQ(0u, inventory[10u].value);
}


// vendor.purchase
TEST_F(VendorTest, purchasable) {
  vendor->input(Money::Hundored);
  vendor->input(Money::Fifty);
  ASSERT_EQ(2u, vendor->getPurchasableList().size());
  EXPECT_EQ(1u, vendor->getPurchasableList().front());
  EXPECT_EQ(3u, vendor->getPurchasableList().back());
}

TEST_F(VendorTest, notPurchasable) {
  vendor->input(Money::Ten);
  EXPECT_TRUE(vendor->getPurchasableList().empty());
}

TEST_F(VendorTest, purchase) {
  vendor->input(Money::Thousand);
  auto actual = vendor->purchase(1u);
  auto inventory = vendor->getInventory();
  ASSERT_TRUE(actual);
  EXPECT_EQ(4u, inventory[1u].num);
  EXPECT_EQ(880u, actual.get());
  EXPECT_EQ(880u, vendor->getTotalAmount());
}

TEST_F(VendorTest, purchaseAndGetZeroChange) {
  vendor->input(Money::Hundored);
  auto actual = vendor->purchase(3u);
  ASSERT_TRUE(actual);
  EXPECT_EQ(0u, actual.get());
}

TEST_F(VendorTest, notPurchase) {
  vendor->input(Money::Hundored);
  auto actual = vendor->purchase(1u);
  auto inventory = vendor->getInventory();
  ASSERT_FALSE(actual);
  EXPECT_EQ(5u, inventory[1u].num);
  EXPECT_EQ(100u, vendor->getTotalAmount());
  EXPECT_EQ(0u, vendor->getSaleAmount());
}

TEST_F(VendorTest, saleAmount) {
  vendor->input(Money::Thousand);
  EXPECT_EQ(0u, vendor->getSaleAmount());
  vendor->purchase(1u);
  EXPECT_EQ(120u, vendor->getSaleAmount());
  vendor->purchase(1u);
  EXPECT_EQ(240u, vendor->getSaleAmount());
}

TEST_F(VendorTest, nothingInventory) {
  vendor->input(Money::Thousand);
  vendor->purchase(1u); vendor->purchase(1u); vendor->purchase(1u); vendor->purchase(1u); vendor->purchase(1u);
  EXPECT_EQ(400u, vendor->getTotalAmount());
  EXPECT_EQ(600u, vendor->getSaleAmount());
  ASSERT_FALSE(vendor->purchase(1u));
  EXPECT_EQ(400u, vendor->getTotalAmount());
  EXPECT_EQ(600u, vendor->getSaleAmount());
}


int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
