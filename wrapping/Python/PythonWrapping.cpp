#include <HelloWorld.hpp>

#include <pybind11/detail/common.h>
#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(MODULE_NAME, m) {
  py::class_<HelloWorld>(m, "HelloWorld")
      // constructors
      .def(py::init<>())
      // member functions
      .def("printHello", &HelloWorld::printHello, "Print 'Hello' to stdout.")
      .def("print", py::overload_cast<std::string>(&HelloWorld::print), "Print a string to stdout.")
      .def("print", py::overload_cast<>(&HelloWorld::print), "Print 'Hello, World!' to stdout.")
      // member variables
      .def_readwrite("prefix", &HelloWorld::prefix);
}
