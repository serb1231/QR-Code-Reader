#include "ModuleA.hpp"

#include <pybind11/operators.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

PYBIND11_MODULE(ModuleA, m) {
  py::class_<HelloWorld>(m, "HelloWorld")
      .def(py::init<>())
      .def("print_something", &HelloWorld::print_something)
      .def("print", &HelloWorld::print);
}
