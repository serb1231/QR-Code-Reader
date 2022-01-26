#pragma once

#include <iostream>
#include <string>

/// HelloWorld Class
/**
   This Class prints "HelloWorld!"
 **/
class HelloWorld {
public:
  /// Constructor of HelloWorld
  HelloWorld() { std::cout << "HelloWorld: Constructor" << std::endl; }
  /// print function prints "HelloWorld!"
  void print() { std::cout << "Hello World!" << std::endl; }
  /// This prints the std::sring simething
  void print_something(std::string something) {
    std::cout << "Something: " << something << std::endl;
  }
};
