#include <GUI.hpp>
#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    // Start GUI
    int err = gui_handler(argc, argv);
    std::cout << "quit the gui handler function" << std::endl;

    return 0;
}
