#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <QRData.hpp>
#include <Decoder.hpp>
#include <ImageFinder.hpp>
#include <ZXEncoder.hpp>
#include <filesystem>

#define STD_PADDING 5 // in pixel
#define STD_SIZE 20   // in pixel

void print_to_decode_output(std::string message, QRData *qrData)
{
    std::cout << message << std::endl;

    // Cast the data pointer to a GtkTextView pointer
    GtkTextView *textview = GTK_TEXT_VIEW(qrData->get_output_decoder_entry());

    // Get the GtkTextBuffer of the decoded_text_textview
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    // Insert the new text into the buffer
    message += "\n";
    const gchar *new_text = message.c_str();
    gtk_text_buffer_insert_at_cursor(buffer, new_text, -1);

    // Scroll the textview to the end
    GtkTextMark *mark = gtk_text_buffer_get_insert(buffer);
    gtk_text_view_scroll_to_mark(textview, mark, 0.0, TRUE, 0.0, 1.0);
}

void print_to_gui_log(std::string message, QRData *qrData)
{
    std::cout << message << std::endl;

    // Cast the data pointer to a GtkTextView pointer
    GtkTextView *textview = GTK_TEXT_VIEW(qrData->get_message_log_textview());

    // Get the GtkTextBuffer of the decoded_text_textview
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(textview);

    // Insert the new text into the buffer
    message += "\n";
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
        print_to_gui_log("Seleced File was not an image", &qrData);
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

    if (std::filesystem::exists(data->get_input_filepath()) == 0)
    {
        print_to_gui_log("Failed to load file! Use \"Open filepath\" first.", data);
        return;
    }

    cv::Mat image = cv::imread(data->get_input_filepath());
    std::string output = dec.decode(image);
    if (output != "No QR code detected!")
    {
        data->set_decoded_text(output);
        print_to_decode_output(output, data);
    }
    else
    {
        print_to_gui_log(output, data);
    }
}

// Button click event handler
void encode_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    auto enc = ZX_Encoder();
    std::string input_text_encoder_entry = gtk_entry_get_text(GTK_ENTRY(data->get_input_text_encoder_entry()));
    std::string path_entry = gtk_entry_get_text(GTK_ENTRY(data->get_output_filepath_entry()));
    std::string input_filename_encoder_entry = gtk_entry_get_text(GTK_ENTRY(data->get_filename_entry()));

    if (path_entry.back() != '/')
    {
        path_entry = path_entry + "/";
    }

    std::string output = enc.encode_text_QRcode(input_text_encoder_entry, input_filename_encoder_entry, path_entry, 500, 20);
    print_to_gui_log(output, data);
    if (output == "Image created successfully!\n")
    {
        std::string full_image_path = path_entry + input_filename_encoder_entry;
        open_image(full_image_path, *data);
    }
}

void path_entry_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    std::string input = gtk_entry_get_text(GTK_ENTRY(data->get_input_filepath_entry()));
    print_to_gui_log("Your entered: " + input, data);

    auto finder = ImageFinder();

    if (finder.CheckPathforImage(input))
    {
        open_image(input, *data);
        data->set_input_filepath(input);
    }
    else
    {
        print_to_gui_log("Filepath does not lead to image. Please try again!", data);
    }
}

void input_explorer_button_clicked(GtkWidget *widget, gpointer user_data)
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

        print_to_gui_log("Selected file: " + filename, data);
        gtk_entry_set_text(GTK_ENTRY(data->get_input_filepath_entry()), filename.c_str());
        data->set_input_filepath(filename);
    }
    else
    {
        print_to_gui_log("File selection canceled by the user", data);
    }

    gtk_widget_destroy(dialog);
}

void output_explorer_button_clicked(GtkWidget *widget, gpointer user_data)
{
    GtkWidget *dialog = gtk_file_chooser_dialog_new(
        "Select Folder",
        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        GTK_FILE_CHOOSER_ACTION_SELECT_FOLDER,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Select", GTK_RESPONSE_ACCEPT,
        NULL);

    QRData *data = static_cast<QRData *>(user_data);

    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT)
    {
        std::string filepath = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        print_to_gui_log("Selected folder: " + filepath, data);
        gtk_entry_set_text(GTK_ENTRY(data->get_output_filepath_entry()), filepath.c_str());
        data->set_output_filepath(filepath);
    }
    else
    {
        print_to_gui_log("File selection canceled by the user", data);
    }

    gtk_widget_destroy(dialog);
}

int gui_handler(int argc, char **argv)
{

    // Initialize GTK
    gtk_init(&argc, &argv);
    QRData qrData = QRData();

    // Color Parameters
    GdkColor color;
    const gchar* background_c = "#efbbcc";
    const gchar* button_c = "#00cdcd";
    const gchar* highlight_c = "#fc8eac";
    const gchar* textfield_c = "#00eeee";

    // Create a GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "QR Coder");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Change color of Background
    gdk_color_parse(background_c, &color);  // Hex color code for pastel blue
    gtk_widget_modify_bg(GTK_WIDGET(window), GTK_STATE_NORMAL, &color);

    // Create a table container
    GtkWidget *table = gtk_table_new(20, 20, false);
    gtk_container_add(GTK_CONTAINER(window), table);

    // Create an entry buffer for manual path and file input for the decoder
    GtkEntryBuffer *input_path_decoder_eBuffer = gtk_entry_buffer_new("filepath to image", -1);
    // Create a text input field
    GtkWidget *input_filepath_decoder_entry = gtk_entry_new_with_buffer(input_path_decoder_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_filepath_decoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filepath_decoder_entry, 2, 18, 2, 3, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Change color of input_filepath_decoder_entry
    gdk_color_parse(textfield_c, &color); 
    gtk_widget_modify_base(input_filepath_decoder_entry, GTK_STATE_NORMAL, &color);

    // Create a GtkTextView widget to display the decoded text
    GtkWidget *decoded_text_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(decoded_text_textview), FALSE);
    GtkWidget *scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), decoded_text_textview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_table_attach(GTK_TABLE(table), scrolled_window, 2, 19, 5, 6, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Change color of decoded_text_textview
    gdk_color_parse(textfield_c, &color); 
    gtk_widget_modify_base(decoded_text_textview, GTK_STATE_NORMAL, &color);

    // Create a GtkTextView widget to display various messages like errors and so on
    GtkWidget *message_log_textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(message_log_textview), FALSE);
    GtkWidget *message_log_textview_scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(message_log_textview_scrolled_window), message_log_textview);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(message_log_textview_scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_table_attach(GTK_TABLE(table), message_log_textview_scrolled_window, 2, 19, 15, 16, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Change color of message_log_textview
    gdk_color_parse(textfield_c, &color); 
    gtk_widget_modify_base(message_log_textview, GTK_STATE_NORMAL, &color);

    // Create a second entry buffer for manual text input for the encoder
    GtkEntryBuffer *input_text_encoder_eBuffer = gtk_entry_buffer_new("input your text here", -1);
    // Create a text input field
    GtkWidget *input_text_encoder_entry = gtk_entry_new_with_buffer(input_text_encoder_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_text_encoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_text_encoder_entry, 2, 19, 11, 12, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Change color of input_text_encoder_entry
    gdk_color_parse(textfield_c, &color); 
    gtk_widget_modify_base(input_text_encoder_entry, GTK_STATE_NORMAL, &color);

    // Create a third entry buffer for manual text input for the filename
    GtkEntryBuffer *input_filename_encoder_eBuffe = gtk_entry_buffer_new("filename (.jpg, .jpeg or .png)", -1);
    // Create a text input field
    GtkWidget *input_filename_encoder_entry = gtk_entry_new_with_buffer(input_filename_encoder_eBuffe);
    gtk_entry_set_visibility(GTK_ENTRY(input_filename_encoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filename_encoder_entry, 2, 4, 9, 10, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Change color of input_filename_encoder_entry
    gdk_color_parse(textfield_c, &color); 
    gtk_widget_modify_base(input_filename_encoder_entry, GTK_STATE_NORMAL, &color);

    // Create an entry buffer for manual path and file input for the decoder
    GtkEntryBuffer *input_path_encoder_eBuffer = gtk_entry_buffer_new("filepath to folder", -1);
    // Create a text input field
    GtkWidget *input_filepath_encoder_entry = gtk_entry_new_with_buffer(input_path_encoder_eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(input_filepath_encoder_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), input_filepath_encoder_entry, 4, 18, 9, 10, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    // Change color of input_filepath_encoder_entry
    gdk_color_parse(textfield_c, &color); 
    gtk_widget_modify_base(input_filepath_encoder_entry, GTK_STATE_NORMAL, &color);

    // Create buttons, attach/place them on the table and connect the signals
    GtkWidget *path_entry_button = gtk_button_new_with_label("Open file from path");
    gtk_table_attach(GTK_TABLE(table), path_entry_button, 2, 3, 3, 4, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    g_signal_connect(path_entry_button, "clicked", G_CALLBACK(path_entry_button_clicked), &qrData);

    // Change color of path_entry_button
    gdk_color_parse (button_c, &color);
    gtk_widget_modify_bg (GTK_WIDGET(path_entry_button), GTK_STATE_NORMAL, &color);
    gdk_color_parse (highlight_c, &color);
    gtk_widget_modify_bg(GTK_WIDGET(path_entry_button), GTK_STATE_PRELIGHT, &color);

    // the explorer button shouldn't have text but only an icon
    GtkWidget *input_explorer_button = gtk_button_new_with_label("");
    GtkWidget *input_explorer_icon = gtk_image_new_from_icon_name("folder", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_image(GTK_BUTTON(input_explorer_button), input_explorer_icon);
    gtk_table_attach(GTK_TABLE(table), input_explorer_button, 18, 19, 2, 3, GTK_SHRINK, GTK_SHRINK, STD_PADDING, STD_PADDING);
    g_signal_connect(input_explorer_button, "clicked", G_CALLBACK(input_explorer_button_clicked), &qrData);

    // Change color of input_explorer_button
    gdk_color_parse (button_c, &color);
    gtk_widget_modify_bg (GTK_WIDGET(input_explorer_button), GTK_STATE_NORMAL, &color);
    gdk_color_parse (highlight_c, &color);
    gtk_widget_modify_bg(GTK_WIDGET(input_explorer_button), GTK_STATE_PRELIGHT, &color);

    GtkWidget *decode_button = gtk_button_new_with_label("Decode QR-Image");
    gtk_table_attach(GTK_TABLE(table), decode_button, 5, 6, 3, 4, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    g_signal_connect(decode_button, "clicked", G_CALLBACK(decode_button_clicked), &qrData);

    // Change color of decode_button
    gdk_color_parse (button_c, &color);
    gtk_widget_modify_bg (GTK_WIDGET(decode_button), GTK_STATE_NORMAL, &color);
    gdk_color_parse (highlight_c, &color);
    gtk_widget_modify_bg(GTK_WIDGET(decode_button), GTK_STATE_PRELIGHT, &color);

    GtkWidget *encode_button = gtk_button_new_with_label("Encode Text to QR-Image");
    gtk_table_attach(GTK_TABLE(table), encode_button, 2, 3, 13, 14, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    g_signal_connect(encode_button, "clicked", G_CALLBACK(encode_button_clicked), &qrData);

    // Change color of encode_button
    gdk_color_parse (button_c, &color);
    gtk_widget_modify_bg (GTK_WIDGET(encode_button), GTK_STATE_NORMAL, &color);
    gdk_color_parse (highlight_c, &color);
    gtk_widget_modify_bg(GTK_WIDGET(encode_button), GTK_STATE_PRELIGHT, &color);

    // the explorer button shouldn't have text but only an icon
    GtkWidget *output_explorer_button = gtk_button_new_with_label("");
    GtkWidget *output_explorer_icon = gtk_image_new_from_icon_name("folder", GTK_ICON_SIZE_BUTTON);
    gtk_button_set_image(GTK_BUTTON(output_explorer_button), output_explorer_icon);
    gtk_table_attach(GTK_TABLE(table), output_explorer_button, 18, 19, 9, 10, GTK_SHRINK, GTK_SHRINK, STD_PADDING, STD_PADDING);
    g_signal_connect(output_explorer_button, "clicked", G_CALLBACK(output_explorer_button_clicked), &qrData);

    // Change color of output_explorer_button
    gdk_color_parse (button_c, &color);
    gtk_widget_modify_bg (GTK_WIDGET(output_explorer_button), GTK_STATE_NORMAL, &color);
    gdk_color_parse (highlight_c, &color);
    gtk_widget_modify_bg(GTK_WIDGET(output_explorer_button), GTK_STATE_PRELIGHT, &color);


    // Setting qrData variables
    qrData.set_input_filepath_entry(input_filepath_decoder_entry);
    qrData.set_output_decoder_entry(decoded_text_textview);
    qrData.set_input_text_encoder_entry(input_text_encoder_entry);
    qrData.set_filename_entry(input_filename_encoder_entry);
    qrData.set_output_filepath_entry(input_filepath_encoder_entry);
    qrData.set_message_log_textview(message_log_textview);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}