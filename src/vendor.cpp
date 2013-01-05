#include "vendor.h"
#include <algorithm>

namespace AutoVendor {

  Vendor::Vendor() : totalAmount(0u), saleAmount(0u) {
    inventory[1u] = {1u, "coke", 5u, 120u};
  }

  void Vendor::input(const Money money) {
    totalAmount += static_cast<unsigned int>(money);
  }

  unsigned int Vendor::getTotalAmount() const {
    return totalAmount;
  }

  const InventoryType Vendor::getInventory() const  {
    return inventory;
  }

  void Vendor::addStock(const Item& item) {
    inventory[item.id] = item;
  }

  const std::list<unsigned int> Vendor::getPurchasableList() const {
    std::list<unsigned int> purchasableList;
    for (auto item : inventory) {
      if (item.second.value <= totalAmount)
        purchasableList.push_back(item.first);
    }
    return purchasableList;
  }

  void Vendor::purchase(unsigned int id) {

    auto purchasable_ =
        [&](const InventoryType::value_type& item) {
            return
              item.first == id
              && item.second.value <= totalAmount
              && item.second.num != 0u;
          };

    auto itr = std::find_if(inventory.begin(), inventory.end(), purchasable_);
    if (itr != inventory.end()) {
      itr->second.num -= 1u;
      totalAmount -= itr->second.value;
      saleAmount += itr->second.value;
    }
  }

  unsigned int Vendor::getSaleAmount() const {
    return saleAmount;
  }
}
