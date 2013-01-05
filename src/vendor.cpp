#include "vendor.h"

namespace AutoVendor {

  Vendor::Vendor() {
    sum = 0;
    sales = 0;
    inventory.insert(InvetoryType::value_type(1, {1u, "coke", 5u, 120u}));
  }

  void Vendor::input(const Money money) {
    sum += static_cast<unsigned int>(money);
  }

  unsigned int Vendor::getSum() const {
    return sum;
  }

  const InvetoryType Vendor::getInventory() const  {
    return inventory;
  }

  void Vendor::addStock(const Item& item) {
    inventory.insert(InvetoryType::value_type(item.id, item));
  }

  const std::list<unsigned int> Vendor::getPurchasableList() const {
    std::list<unsigned int> purchasableList;
    for (auto i : inventory) {
      if (i.second.value <= sum) purchasableList.push_back(i.first);
    }
    return purchasableList;
  }

  void Vendor::purchase(unsigned int id) {
    auto itr = inventory.find(id);
    if (itr != inventory.end()
        && itr->second.value <= sum
        && itr->second.num != 0) {
      itr->second.num -= 1;
      sum -= itr->second.value;
      sales += itr->second.value;
    }
  }

  unsigned int Vendor::getSales() const {
    return sales;
  }
}
