#include <HelloWorld.hpp>

HelloWorld::HelloWorld() {
  std::cout << "HelloWorld: Constructor" << std::endl;
}

void HelloWorld::printHello() { std::cout << prefix << "Hello"; }

void HelloWorld::print() { std::cout << prefix << "Hello World!" << std::endl; }

void HelloWorld::print(std::string something) {
  std::cout << prefix << something << std::endl;
}
