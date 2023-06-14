#include <iostream>
#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <stdio.h>
#include <QRData.hpp>

void on_dialog_response(GtkDialog *dialog, gint response_id, gpointer user_data)
{
    std::string selectedFile;
    QRData *data = static_cast<QRData *>(user_data);
    if (response_id == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *filechooser = GTK_FILE_CHOOSER(dialog);
        selectedFile = gtk_file_chooser_get_filename(filechooser);

        std::cout << "Selected file: " << selectedFile << std::endl;

        data->set_input_filepath(selectedFile);
    }
    else
    {
        std::cout << "File selection canceled by the user." << std::endl;
    }

    gtk_widget_destroy(GTK_WIDGET(dialog));
    gtk_main_quit();
}

int main()
{
    // Initialize GTK
    gtk_init(NULL, NULL);
    std::string selectedFile;

    // Create a file chooser dialog
    GtkWidget *filechooserdialog = gtk_file_chooser_dialog_new(
        "Choose files to read",
        GTK_WINDOW(gtk_window_new(GTK_WINDOW_TOPLEVEL)),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel",
        GTK_RESPONSE_CANCEL,
        "Open",
        GTK_RESPONSE_ACCEPT,
        NULL);

    QRData explorer = QRData();
    // Connect the response signal to the callback function
    g_signal_connect(filechooserdialog, "response", G_CALLBACK(on_dialog_response), &explorer);

    // Show the file chooser dialog
    gtk_widget_show_all(filechooserdialog);

    // Run the GTK main loop
    gtk_main();

    // Getting Filename obtained in on_dialog_response
    selectedFile = explorer.get_input_filepath();

    // Displaying Image
    cv::Mat image;
    image = cv::imread(selectedFile, 1);

    if (!image.data)
    {
        printf("Seleced File was not an image \n");
        return -1;
    }

    cv::namedWindow("Selected Image:", cv::WINDOW_AUTOSIZE);
    cv::imshow("Selected Image:", image);
    cv::waitKey(0);

    return 0;
}
