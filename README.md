# QR Code Reader in C++

This project's aim is to deliver a program capable of offering its users a seamless experience when dealing with QR Codes. It is possible to choose a file via a file explorer and if it is a QR Code to decode it. Another use case is encoding some text and saving it as a QR Code. 

## Dependencies

To achieve this the project uses the following libraries:

+ doxygen version 1.9.2: A documentation generator for generating project documentation
+ opencv version 4.5.5: A computer vision library for image processing and computer vision algorithms
+ zxing-cpp version 2.0.0: A C++ port of the ZXing library for QR code encoding and decoding 
+ stb version cci.20220909: A collection of single-file public domain libraries for C/C++ 

## Building the Project

To build the project locally, you need to ensure that the appropriate settings are set in the Conan profile file. The Conan package manager is used to handle the project's dependencies.

Please follow the steps below to configure the Conan profile
1. Locate the Conan profile file. The default location for the profile file is usually 

       ~/.conan/profiles/default

2. Open the profile file using a text editor.
3. Verify that the following settings are added at the bottom in the profile file: 

       [env]
       tools.system.package_manager:mode = install
       tools.system.package_manager:sudo = True

4. Save the changes to the profile file.
Once you have configured the Conan profile, you can proceed with building the project.

## Building Instructions

To build the project, follow these steps:

5. Clone the project repository: 

       https://stea.iue.tuwien.ac.at/CppProjects2023/GroupNProject.git

6. Change to the project directory: 
     
       cd GroupNProject

7. Create a build directory: 
          
       mkdir build
       cd build

8. Initialize Conan: 

       conan install ..

9. Configure the build system (CMake):

       cmake ..

10. Build the project:

        make

11. Switch to the bin directory:

        cd bin

12. Run the project:

        ./UI_test

Please note: these instructions assume you have already installed the required dependencies and have a suitable C++ compiler installed on your system.

## Usage
Once the project is built and running, this program is capable of doing two different separate operations:

### QR Decoder 
The decoder enables you to decode QR-codes into text that is then output to the first text output field. 
To achieve a successful decode, make sure to follow the following steps:

+ Chose a file via the file explorer or input the file path leading to an image manually
+ If file was chosen manually, press "Open file from path"
+ If file path was correct, the image should open in a separate window
+ Press "Decode QR Image"
+ If the decoder fails or the file path does not lead to an image, an error message should appear in the bottom text output field

### QR Encoder
The encoder allows you to encode any text into a QR Code that is then saved as an image. 
To achieve a successful encode, make sure to follow these steps:

+ Input a filename for the created image <br>
+ The filename must end with a supported file extension. Supported file types are: .png, .jpeg and .jpg <br>
+ Input a file path to where the image should be saved <br>
+ File path can end with "/", but does not have to <br>
+ Enter the text you want to encode <br>
+ Press "Encode Text to QR Image" <br>

If every input was correct the message "Image created successfully!" should appear and the newly created image is opened in a separate window. 
Any error that occurs when trying to encode should be output to the bottom text output field. Errors could be wrong filepath, missing file extension, missing text to encode… Type of error should be easily recognizable through the error message.

## Documentation

The project documentation can be generated using Doxygen. To generate the documentation, execute the following command in the project root directory:

    doxygen Doxyfile

The generated documentation will be available in the docs directory.

## License
This project is licensed under the GNU GENERAL PUBLIC LICENSE

## Team
- Maximilian Seiringer (12030168)
- Lukas Buza (11917677)
- Matteo Ingegneri (11917678)
- Mario Lang (11901887)
- Lucas Minarik (01608718)
- Serban-Mihai Ionescu  (12202437)


## References
[1] https://opencv.org/<br>
[2] https://learnopencv.com/opencv-qr-code-scanner-c-and-python/<br>
