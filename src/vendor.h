#pragma once

#include <map>
#include <string>
#include <list>

namespace AutoVendor {

  enum class Money : unsigned int {
    Thousand = 1000,
    FiveHundored = 500,
    Hundored = 100,
    Fifty = 50,
    Ten = 10
  };

  struct Item {
    unsigned int id;
    std::string name;
    unsigned int num;
    unsigned int value;
  };


  using InvetoryType = std::map<unsigned int, Item>;

  class Vendor {
    unsigned int totalAmount;
    unsigned int saleAmount;
    InvetoryType inventory;
  public:
    Vendor();
    void input(const Money);
    unsigned int getTotalAmount() const;
    const InvetoryType getInventory() const;
    void addStock(const Item&);
    const std::list<unsigned int> getPurchasableList() const;
    void purchase(unsigned int);
    unsigned int getSaleAmount() const;
  };
}

