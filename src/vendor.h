#ifndef __VENDOR_H
#define __VENDOR_H

#include <stdexcept>

namespace AutoVendor {

  enum class Money : unsigned int {
    Thousand = 1000,
    FiveHundored = 500,
    Hundored = 100,
    Fifty = 50,
    Ten = 10
  };


  struct Vendor {
    unsigned int sum;

    Vendor(){};

    void input(const Money money);
    unsigned int getSum() const;
  };
}

#endif // __VENDOR_H
