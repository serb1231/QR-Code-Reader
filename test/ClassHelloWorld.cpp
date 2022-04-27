#include <HelloWorld.hpp>

#include "testasserts.hpp"

int main() {
  auto hw = HelloWorld();

  TEST_ASSERT(hw.prefix == "", "Default prefix is not empty!");

  hw.prefix = "myMessage";
  TEST_ASSERT(hw.prefix == "myMessage", "Setting prefix failed!");

  return 0;
}
