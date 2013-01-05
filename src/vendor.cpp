#include "vendor.h"

namespace AutoVendor {

  Vendor::Vendor() : totalAmount(0), saleAmount(0) {
    inventory.insert(InvetoryType::value_type(1, {1u, "coke", 5u, 120u}));
  }

  void Vendor::input(const Money money) {
    totalAmount += static_cast<unsigned int>(money);
  }

  unsigned int Vendor::getTotalAmount() const {
    return totalAmount;
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
      if (i.second.value <= totalAmount) purchasableList.push_back(i.first);
    }
    return purchasableList;
  }

  void Vendor::purchase(unsigned int id) {

    auto purchasable_ =
        [&](InventoryType::value_type item) {
            return
              item.first == id
              && item.second.value <= totalAmount
              && item.second.num != 0;
          };

    auto itr = std::find_if(inventory.begin(), inventory.end(), purchasable_);
    if (itr != inventory.end()) {
      itr->second.num -= 1;
      totalAmount -= itr->second.value;
      saleAmount += itr->second.value;
    }
  }

  unsigned int Vendor::getSaleAmount() const {
    return saleAmount;
  }
}
