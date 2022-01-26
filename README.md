# ViennaTestProject

This repository should give an impression how C++ and Python could work together with pybind11, using cmake as an build-environment and doxygen for documentation.
## Building

```
mkdir build && cd build
cmake ..
make
```

## Installing 
To install the built python library run:

```
cd lib/
pip3 install -e .
```

to test your installation you can run the example.

## Documentation

The doxygen config can be found in the ``doc`` folder. The documentation is built with cmake in the build-dir.

## Contributing

Please run ``format-project.sh`` before commiting.



## Authors
ViennaTestProject was developed under the aegis of the 'Institute for Microelectronics' at the 'TU Wien'.
http://www.iue.tuwien.ac.at/

License
--------------------------
See file LICENSE in the base directory.
