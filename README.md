# QRCoder

This repository should give an impression how C++ and Python could work together with pybind11, using cmake as an build-environment and doxygen for documentation.

--------------------------

## How to Use

This program is capable of doing 2 different separate operations:
### QR-Decoder. 
The decoder enables you to decode QR-codes into text that is then output to the first text output field. 
To achieve a successful decode make sure to follow these steps:
1. Chose a file via the file explorer or input the file path leading to an image manually.
    - If file was chosen manually, press “Open file from path”. If file path was correct, the image should open in a separate window.
2. Press “Decode QR-Image”.

If the decoder fails or the file path does not lead to an image, an error message should appear in the bottom text output field. 

### QR-Encoder
The encoder allows you to encode any text into an QR-Code that is then saved as an image. To achieve a successful encode, make sure to follow these steps:
1. Input a filename for the created image. 
    - Filename must end with supported file extension. Supported file types are .png, .jpeg and .jpg.
2. Input a file path to where the image should be saved.
    - File path can end with “/”, but does not have to.
3. Enter the text you want to encode.
4. Press “Encode Text to QR-Image”.

If every input was correct the message “Image created successfully!” should appear and the newly created image is opened in a separate window.
Any error that occurs when trying to encode should be output to the bottom text output field.
Errors could be wrong filepath, missing file extension, missing text to encode… 
Type of error should be easily recognizable through the error message.

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
ViennaExample was developed under the aegis of the 'Institute for Microelectronics' at the 'TU Wien'.
http://www.iue.tuwien.ac.at/

--------------------------
## License
See file LICENSE in the base directory.
q

