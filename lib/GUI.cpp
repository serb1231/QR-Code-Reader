#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <QRData.hpp>
#include <Decoder.hpp>
#include <ImageFinder.hpp>

#define STD_PADDING 5

void open_image(const std::string &path, QRData *qrData)
{
    // cv::Mat image_file = cv::imread(path);
    // GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(
    //     image_file.data,
    //     GDK_COLORSPACE_RGB,
    //     false,
    //     8,
    //     image_file.cols,
    //     image_file.rows,
    //     image_file.step,
    //     nullptr,
    //     nullptr);

    // gtk_image_set_from_pixbuf(GTK_IMAGE(qrData->get_image_widget()), pixbuf);
    // Displaying Image
    cv::Mat image;
    image = cv::imread(path, 1);

    if (!image.data)
    {
        printf("Seleced file was not an image\n");
        return;
    }

    cv::namedWindow("Selected Image:", cv::WINDOW_AUTOSIZE);
    cv::imshow("Selected Image:", image);
    cv::waitKey(0);
}

// Button click event handler
void decode_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    auto dec = Decoder();

    cv::Mat image = cv::imread(data->get_input_filepath());
    std::string output = dec.decode(image);
    if (output != "No QR code detected!")
    {
        data->set_decoded_text(output);
    }
    std::cout << output << std::endl;

    // Cast the data pointer to a GtkTextView pointer
    GtkTextView *output_decoder_textfield = GTK_TEXT_VIEW(data->get_output_decoder_textfield());

    // Get the GtkTextBuffer of the output_decoder_textfield
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(output_decoder_textfield);

    // Clear the existing text in the buffer
    gtk_text_buffer_set_text(buffer, "", -1);

    // Insert the new text into the buffer
    const gchar *new_text = output.c_str();
    gtk_text_buffer_insert_at_cursor(buffer, new_text, -1);
}

void path_button_clicked(GtkWidget *widget, gpointer user_data)
{
    g_print("You entered: ");

    QRData *data = static_cast<QRData *>(user_data);

    std::string input = gtk_entry_get_text(GTK_ENTRY(data->get_input_filepath_textfield()));
    std::cout << input << std::endl;

    auto finder = ImageFinder();

    if (finder.CheckPathforImage(input))
    {
        open_image(input, data);
        data->set_input_filepath(input);
    }
    else
    {
        g_print("Filepath does not lead to image. Please try again!\n");
    }
}

void browse_button_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Open", GTK_RESPONSE_ACCEPT,
        NULL);

    QRData *data = static_cast<QRData *>(user_data);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT)
    {
        char *filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        open_image(filename, data);

        g_print("Selected file:%s\n", filename);

        data->set_input_filepath(filename);
    }
    else
    {
        g_print("File selection canceled by the user\n");
    }

    gtk_widget_destroy(dialog);
}

int gui_handler(int argc, char **argv)
{
    // Initialize GTK
    gtk_init(&argc, &argv);
    // struct to hold useful values
    QRData qrData = QRData();

    // Create a GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a table container and add it to window
    GtkWidget *table = gtk_table_new(10, 10, false);
    gtk_container_add(GTK_CONTAINER(window), table);

    // Create an input_filepath_textfield buffer
    GtkEntryBuffer *input_path_eBuffer = gtk_entry_buffer_new("filepath", -1);
    // Create a text input field and add it to table
    GtkWidget *input_filepath_textfield = gtk_entry_new_with_buffer(input_path_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_filepath_textfield), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filepath_textfield, 1, 2, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create a GtkTextView widget with appropriate settings and add it to window
    GtkWidget *output_decoder_textfield = gtk_text_view_new();
    gtk_table_attach(GTK_TABLE(table), output_decoder_textfield, 1, 7, 3, 5, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create three buttons, connect them to their handlers and attach them to the table
    GtkWidget *path_button = gtk_button_new_with_label("Use input path");
    // Connect the "path_button" signal to the signal handler
    qrData.set_input_filepath_textfield(input_filepath_textfield);
    qrData.set_output_decoder_textfield(output_decoder_textfield);
    g_signal_connect(path_button, "clicked", G_CALLBACK(path_button_clicked), &qrData);
    gtk_table_attach(GTK_TABLE(table), path_button, 1, 2, 2, 3, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    GtkWidget *browser_button = gtk_button_new_with_label("Open Explorer");
    g_signal_connect(browser_button, "clicked", G_CALLBACK(browse_button_clicked), &qrData);
    gtk_table_attach(GTK_TABLE(table), browser_button, 3, 5, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    GtkWidget *decode_button = gtk_button_new_with_label("Decode QR-Image");
    g_signal_connect(decode_button, "clicked", G_CALLBACK(decode_button_clicked), &qrData);
    gtk_table_attach(GTK_TABLE(table), decode_button, 5, 7, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // create an image display container to show the selected file
    GtkWidget *file_display = gtk_image_new();
    gtk_table_attach(GTK_TABLE(table), file_display, 1, 7, 5, 10, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    qrData.set_image_widget(file_display);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
