#pragma once

#include <map>
#include <vector>
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

  class Vendor {
    unsigned int sum;
    unsigned int sales;
    std::map<unsigned int, Item> inventory;
  public:
    Vendor();
    void input(const Money);
    unsigned int getSum() const;
    const std::map<unsigned int, Item> getInventory() const;
    void addStock(const Item&);
    const std::list<unsigned int> getPurchasableList() const;
    void purchase(unsigned int);
    unsigned int getSales() const;
  };
}

