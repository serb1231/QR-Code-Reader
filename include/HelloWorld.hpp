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
  /// print function prints "HelloWorld!"
  void print();
  /// This prints the std::sring simething
  void print(std::string something);
};
