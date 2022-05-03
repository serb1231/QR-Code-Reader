# ViennaExample

This repository should give an impression how C++ and Python could work together with pybind11, using cmake as an build-environment and doxygen for documentation.

--------------------------
## Pre-Requisits

- `conan` (for dependency management)
- `CMake`
- `C++17 Compiler`
- `python3`
- `python3-pip`
- `python3-venv`

### Supported Platforms

Currently, only **Linux** is supported and tested for. If you find problems for Windows/Mac please let us know how you solved them!

--------------------------
## Building

```
mkdir build && cd build
cmake ..
make
```

### Building the python module

```
mkdir build && cd build
cmake .. -D BUILD_PYTHON=ON
make
```

The built python wheel is then under `build/wheel/ViennaExample*.whl`.
In order to install the package, run:
```
cd build
python3 -m venv venv # create virtual environment
source venv/bin/activate
pip3 install wheel/ViennaExample-*-*.whl # this will depend on the library version
# Test the installed module by running the example
../example/HelloWorld.py
```

--------------------------
## Installing

To install all targets to a local folder:
```
cd build
cmake ..
make install
```

--------------------------
## Testing

To run the tests:
```
cd build
cmake ..
make buildtests
make buildpytests
make test
```

--------------------------
## Documentation

To build the documentation:
```
cd build
cmake -D BUILD_DOCS=ON ..
make docs
```

--------------------------
## Contributing

Please run ``format-project.sh`` before commiting.

--------------------------
## Authors
ViennaTestProject was developed under the aegis of the 'Institute for Microelectronics' at the 'TU Wien'.
http://www.iue.tuwien.ac.at/

--------------------------
## License
See file LICENSE in the base directory.
