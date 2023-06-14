cmake_minimum_required(VERSION 3.7...3.22)

# set up the project for building all tests
project(Tests LANGUAGES CXX)

# make a custom target for usage with make
# all tests can be built using `make buildtests`
set(TEST_BUILD_TARGET buildtests)
add_custom_target(${TEST_BUILD_TARGET} ALL)

set(MY_TEST_NAMES "")
list(APPEND MY_TEST_NAMES "Startup_GUI")

foreach(MY_TEST_NAME ${MY_TEST_NAMES})
  # build test executable and link project library
  add_executable(${MY_TEST_NAME} ${MY_TEST_NAME}.cpp testasserts.hpp)
  target_link_libraries(${MY_TEST_NAME} PRIVATE ${PROJECT_ROOT_NAME} ${OpenCV_LIBS})

  # Add to test framework, so test can be built with `make myTests`
  add_dependencies(${TEST_BUILD_TARGET} ${MY_TEST_NAME})
  add_test(NAME ${MY_TEST_NAME} COMMAND ${MY_TEST_NAME})

endforeach(MY_TEST_NAME ${MY_TEST_NAMES})

