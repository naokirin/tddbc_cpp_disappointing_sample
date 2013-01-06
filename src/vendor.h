#pragma once

#include <map>
#include <string>
#include <list>
#include <boost/optional.hpp>

namespace AutoVendor {

  enum class Money : unsigned int {
    Thousand = 1000u,
    FiveHundored = 500u,
    Hundored = 100u,
    Fifty = 50u,
    Ten = 10u
  };

  struct Item {
    unsigned int id;
    std::string name;
    unsigned int num;
    unsigned int value;
  };


  using InventoryType = std::map<unsigned int, Item>;

  class Vendor {
    unsigned int totalAmount;
    unsigned int saleAmount;
    InventoryType inventory;
  public:
    Vendor();
    void input(const Money);
    unsigned int getTotalAmount() const;
    const InventoryType getInventory() const;
    void addStock(const Item&);
    const std::list<unsigned int> getPurchasableList() const;
    boost::optional<unsigned int> purchase(unsigned int);
    unsigned int getSaleAmount() const;
  };
}

