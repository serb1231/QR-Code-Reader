#pragma once

#include <iostream>
#include <string>

/// HelloWorld Class
/**
   This Class prints "HelloWorld!"
 **/
struct HelloWorld {
  std::string prefix;
  /// Constructor of HelloWorld
  HelloWorld();
  /// This function just prints "Hello"
  void printHello();
  /// Prints "HelloWorld!"
  void print();
  /// This prints the std::sring something
  void print(std::string something);
};
