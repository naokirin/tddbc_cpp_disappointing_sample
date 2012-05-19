#include "vendor.h"

void AutoVendor::Vendor::input(const AutoVendor::Money money) {
  sum += static_cast<int>(money);
}

unsigned int AutoVendor::Vendor::getSum() const {
  return sum;
}
