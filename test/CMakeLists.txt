cmake_minimum_required(VERSION 3.7...3.22)

# set up the project for building all tests
project(Tests LANGUAGES CXX)

# make a custom target for usage with make
# all tests can be built using `make buildtests`
set(TEST_BUILD_TARGET buildtests)
add_custom_target(${TEST_BUILD_TARGET} ALL)

set(MY_TEST_NAMES "")
list(APPEND MY_TEST_NAMES "ClassDecoder")
list(APPEND MY_TEST_NAMES "ClassZXEncoder")
list(APPEND MY_TEST_NAMES "UI_test")
#list(APPEND MY_TEST_NAMES "ClassGtkFileExplorer")
list(APPEND MY_TEST_NAMES "ClassOutput")



foreach(MY_TEST_NAME ${MY_TEST_NAMES})
  # build test executable and link project library
  add_executable(${MY_TEST_NAME} ${MY_TEST_NAME}.cpp testasserts.hpp)
  target_link_libraries(${MY_TEST_NAME} PRIVATE ${PROJECT_ROOT_NAME})

  # Add to test framework, so test can be built with `make myTests`
  add_dependencies(${TEST_BUILD_TARGET} ${MY_TEST_NAME})
  add_test(NAME ${MY_TEST_NAME} COMMAND ${MY_TEST_NAME})
endforeach(MY_TEST_NAME ${MY_TEST_NAMES})


if(BUILD_PYTHON)

find_package(Python3 COMPONENTS Interpreter REQUIRED)
set(VENV ${CMAKE_BINARY_DIR}/venv)
set(REQUIREMENTS ${CMAKE_SOURCE_DIR}/python/requirements.txt)
set(OUTPUT_FILE ${VENV}/environment.txt)

set(PY_BIN_DIR ${VENV}/bin)
set(PYTHON3 ${PY_BIN_DIR}/python3)
set(PIP3 ${PY_BIN_DIR}/pip3)

add_custom_command(
            OUTPUT ${OUTPUT_FILE}
            COMMAND ${Python3_EXECUTABLE} -m venv ${VENV}
            COMMAND ${PIP3} install -r ${REQUIREMENTS}
            COMMAND ${PIP3} install -e ${CMAKE_BINARY_DIR}/wheel
            COMMAND ${PIP3} freeze > ${VENV}/environment.txt
            DEPENDS ${REQUIREMENTS}
    )

add_custom_target(venv DEPENDS ${OUTPUT_FILE})

set(TEST_BUILD_TARGET buildpytests)
add_custom_target(${TEST_BUILD_TARGET} ALL DEPENDS venv)

set(MY_TEST_NAMES "")
list(APPEND MY_TEST_NAMES "ClassHelloWorld")

foreach(MY_TEST_NAME ${MY_TEST_NAMES})

  add_test(NAME PY_${MY_TEST_NAME} COMMAND ${PYTHON3} ${CMAKE_CURRENT_SOURCE_DIR}/${MY_TEST_NAME}.py)
  
endforeach(MY_TEST_NAME ${MY_TEST_NAMES})

 
endif()
