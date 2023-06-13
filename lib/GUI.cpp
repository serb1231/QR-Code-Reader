#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <QRData.hpp>
#include <Decoder.hpp>
#include <ImageFinder.hpp>
#include <ZXEncoder.hpp>
#include <filesystem>

#define STD_PADDING 5

void print_to_gui_log(std::string message, QRData *qrData)
{
    g_print("%s", message);

    // Cast the data pointer to a GtkTextView pointer
    GtkTextView *textview = GTK_TEXT_VIEW(qrData->get_message_log_textview());

    // Get the GtkTextBuffer of the decoded_text_textview
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    // Insert the new text into the buffer
    const gchar *new_text = message.c_str();
    gtk_text_buffer_insert_at_cursor(buffer, new_text, -1);

    // Scroll the textview to the end
    GtkTextMark *mark = gtk_text_buffer_get_insert(buffer);
    gtk_text_view_scroll_to_mark(textview, mark, 0.0, TRUE, 0.0, 1.0);
}

void open_image(const std::string &path, QRData qrData)
{
    // Displaying Image
    cv::Mat image;
    image = cv::imread(path, 1);

    if (!image.data)
    {
        print_to_gui_log("Seleced File was not an image\n", &qrData);
        return;
    }

    cv::namedWindow("Selected Image:", cv::WINDOW_AUTOSIZE);
    cv::imshow("Selected Image:", image);
    cv::waitKey(0);
}

void decode_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    auto dec = Decoder();

    cv::Mat image = cv::imread(data->get_input_filepath());
    std::string output = "\n" + dec.decode(image);
    if (output != "No QR code detected!")
    {
        data->set_decoded_text(output);
    }
    print_to_gui_log(output + "\n", data);
}

// Button click event handler
void encode_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    auto enc = ZX_Encoder();
    std::string input_text_encoder_entry = gtk_entry_get_text(GTK_ENTRY(data->get_input_text_encoder_entry()));
    std::string path_entry = gtk_entry_get_text(GTK_ENTRY(data->get_input_filepath_textfield()));
    std::string input_filename_encoder_entry = gtk_entry_get_text(GTK_ENTRY(data->get_filename_entry()));

    std::string output = enc.encode_text_QRcode(input_text_encoder_entry, input_filename_encoder_entry, path_entry, 100, 0);
    print_to_gui_log(output, data);
    if (output == "Image created successfully!\n")
    {
        std::string full_image_path = path_entry + input_filename_encoder_entry;
        open_image(full_image_path, *data);
    }
    else
    {
        std::cout << output << std::endl;
    }
}

void path_entry_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    std::string input = gtk_entry_get_text(GTK_ENTRY(data->get_input_filepath_textfield()));
    print_to_gui_log("Your entered: " + input + "\n", data);

    auto finder = ImageFinder();

    if (finder.CheckPathforImage(input))
    {
        open_image(input, *data);
        data->set_input_filepath(input);
    }
    else
    {
        print_to_gui_log("Filepath does not lead to image. Please try again!\n", data);
    }
}

void explorer_button_clicked(GtkWidget *widget, gpointer user_data)
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
        std::string filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        open_image(filename, *data);

        print_to_gui_log("Selected file: " + filename + "\n", data);
        gtk_entry_set_text(GTK_ENTRY(data->get_input_filepath_textfield()), filename.c_str());
        data->set_input_filepath(filename);
    }
    else
    {
        print_to_gui_log("File selection canceled by the user\n", data);
    }

    gtk_widget_destroy(dialog);
}

int gui_handler(int argc, char **argv)
{

    // Initialize GTK
    gtk_init(&argc, &argv);
    QRData qrData = QRData();

    // Create a GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a table container
    GtkWidget *table = gtk_table_new(200, 200, false);
    gtk_container_add(GTK_CONTAINER(window), table);

    // GtkWidget *fixed = gtk_fixed_new();
    // gtk_container_add(GTK_CONTAINER(window), fixed);

    // // Create a GTK Notebook
    // GtkWidget *notebook = gtk_notebook_new();
    // gtk_container_add(GTK_CONTAINER(window), notebook);

    // GtkWidget *page1 = gtk_label_new("Decoder");
    // GtkWidget *page2 = gtk_label_new("Encoder");

    // gtk_notebook_append_page(GTK_NOTEBOOK(notebook), table, page1);
    // gtk_notebook_append_page(GTK_NOTEBOOK(notebook), fixed, page2);

    // Create an entry buffer for manual path and file input for the decoder
    GtkEntryBuffer *input_path_decoder_eBuffer = gtk_entry_buffer_new("filepath to image", -1);
    // Create a text input field
    GtkWidget *input_filepath_decoder_entry = gtk_entry_new_with_buffer(input_path_decoder_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_filepath_decoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filepath_decoder_entry, 2, 12, 2, 3, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create a GtkTextView widget to display the decoded text
    GtkWidget *decoded_text_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(decoded_text_textview), FALSE);
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), decoded_text_textview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_table_attach(GTK_TABLE(table), scrolled_window, 2, 15, 6, 7, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create a GtkTextView widget to display various messages like errors and so on
    GtkWidget *message_log_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(message_log_textview), FALSE);
    GtkWidget *message_log_textview_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(message_log_textview_scrolled_window), message_log_textview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(message_log_textview_scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_table_attach(GTK_TABLE(table), message_log_textview_scrolled_window, 2, 15, 100, 207, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create a second entry buffer for manual text input for the encoder
    GtkEntryBuffer *input_text_encoder_eBuffer = gtk_entry_buffer_new("input your text here", -1);
    // Create a text input field
    GtkWidget *input_text_encoder_entry = gtk_entry_new_with_buffer(input_text_encoder_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_text_encoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_text_encoder_entry, 2, 15, 10, 11, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create a third entry buffer for manual text input for the filename
    GtkEntryBuffer *input_filename_encoder_eBuffe = gtk_entry_buffer_new("filename (.jpg or .png)", -1);
    // Create a text input field
    GtkWidget *input_filename_encoder_entry = gtk_entry_new_with_buffer(input_filename_encoder_eBuffe);
    gtk_entry_set_visibility(GTK_ENTRY(input_filename_encoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filename_encoder_entry, 13, 15, 8, 9, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create an entry buffer for manual path and file input for the decoder
    GtkEntryBuffer *input_path_encoder_eBuffer = gtk_entry_buffer_new("filepath to folder", -1);
    // Create a text input field
    GtkWidget *input_filepath_encoder_entry = gtk_entry_new_with_buffer(input_path_encoder_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_filepath_encoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filepath_encoder_entry, 2, 11, 8, 9, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Create buttons, attach them/place them on the table and connect the signals
    GtkWidget *path_entry_button = gtk_button_new_with_label("Open file from path");
    gtk_table_attach(GTK_TABLE(table), path_entry_button, 2, 3, 4, 5, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    g_signal_connect(path_entry_button, "clicked", G_CALLBACK(path_entry_button_clicked), &qrData);

    GtkWidget *explorer_button = gtk_button_new_with_label("");
    GtkWidget *explorer_icon = gtk_image_new_from_icon_name("folder", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_image(GTK_BUTTON(explorer_button), explorer_icon);
    gtk_table_attach(GTK_TABLE(table), explorer_button, 14, 15, 2, 3, GTK_SHRINK, GTK_SHRINK, STD_PADDING, STD_PADDING);
    g_signal_connect(explorer_button, "clicked", G_CALLBACK(explorer_button_clicked), &qrData);

    GtkWidget *decode_button = gtk_button_new_with_label("Decode QR-Image");
    gtk_table_attach(GTK_TABLE(table), decode_button, 8, 9, 4, 5, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    g_signal_connect(decode_button, "clicked", G_CALLBACK(decode_button_clicked), &qrData);

    GtkWidget *encode_button = gtk_button_new_with_label("Encode Text to QR-Image");
    // gtk_table_attach(GTK_TABLE(table), encode_button, 2, 3, 12, 13, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    g_signal_connect(encode_button, "clicked", G_CALLBACK(encode_button_clicked), &qrData);

    // Setting qrData variables
    qrData.set_input_filepath_textfield(input_filepath_decoder_entry);
    qrData.set_output_decoder_textfield(decoded_text_textview);
    qrData.set_input_text_encoder_entry(input_text_encoder_entry);
    qrData.set_filename_entry(input_filename_encoder_entry);
    qrData.set_message_log_textview(message_log_textview);

    gtk_fixed_put(GTK_FIXED(fixed), encode_button, 50, 50);
    gtk_widget_set_size_request(encode_button, 100, 30);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
