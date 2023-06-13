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

void open_image(const std::string& path){

        // Displaying Image
        cv::Mat image;
        image = cv::imread(path, 1);

        if (!image.data)
        {
            printf("Seleced File was not an image \n");
            return;
        
        }

        cv::namedWindow("Selected Image:", cv::WINDOW_AUTOSIZE);
        cv::imshow("Selected Image:", image);
        cv::waitKey(0);

}


// Button click event handler
void decode_button_clicked(GtkWidget *widget, gpointer user_data)
{
    //g_print("Button clicked!\n");
    QRData *data = static_cast<QRData *>(user_data);

    auto dec = Decoder();

    cv::Mat image = cv::imread(data->get_input_filepath());
    std::string output = dec.decode(image);
    if(output != "No QR code detected!"){
        data->set_decoded_text(output);
    }
    std::cout <<output << std::endl;

    // Cast the data pointer to a GtkTextView pointer
    GtkTextView* textview = GTK_TEXT_VIEW(data->get_textfield());

    // Get the GtkTextBuffer of the textview
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(textview);

    // Clear the existing text in the buffer
    gtk_text_buffer_set_text(buffer, "", -1);

    // Insert the new text into the buffer
    const gchar* new_text = output.c_str();
    gtk_text_buffer_insert_at_cursor(buffer, new_text, -1);

}

// Button click event handler
void encode_button_clicked(GtkWidget *widget, gpointer user_data)
{
    QRData *data = static_cast<QRData *>(user_data);

    auto enc = ZX_Encoder();
    std::string text_entry = gtk_entry_get_text(GTK_ENTRY(data->get_text_entry()));
    std::string path_entry = gtk_entry_get_text(GTK_ENTRY(data->get_file_entry()));
    std::string filename_entry = gtk_entry_get_text(GTK_ENTRY(data->get_filename_entry()));
    
    //Filepath needs to end with / to work with Encode function
    if(path_entry.back()!='/'){
        path_entry = path_entry + "/";
    }


	std::string err = enc.encode_text_QRcode(text_entry , filename_entry, path_entry, 100, 0);

    if(err == "Image created successfully!\n"){
        std::string full_image_path = path_entry + filename_entry;
        open_image(full_image_path);
    }else{
        std::cout << err << std::endl;
    }

}


void file_entry_button_clicked(GtkWidget* widget, gpointer user_data) {
    g_print("You entered: ");

    QRData *data = static_cast<QRData *>(user_data);

    std::string input = gtk_entry_get_text(GTK_ENTRY(data->get_file_entry()));
    std::cout << input << std::endl;
    
    auto finder= ImageFinder();

    if(finder.CheckPathforImage(input)){
        open_image(input);
        data->set_input_filepath(input);
    }else{
        g_print("Filepath does not lead to image. Please try again!\n");
    }

}

void open_filebrowser(GtkWidget *widget, gpointer user_data) {
    GtkWidget* dialog = gtk_file_chooser_dialog_new(
        "Open File",
        GTK_WINDOW(gtk_widget_get_toplevel(widget)),
        GTK_FILE_CHOOSER_ACTION_OPEN,
        "Cancel", GTK_RESPONSE_CANCEL,
        "Open", GTK_RESPONSE_ACCEPT,
        NULL
    );

    QRData *data = static_cast<QRData *>(user_data);


    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        open_image(filename);

        g_print("Selected file:%s\n",filename);

        data->set_input_filepath(filename);

    }else{
        g_print("File selection canceled by the user\n");
    }

    gtk_widget_destroy(dialog);
}


int gui_handler(int argc, char** argv) {

// Initialize GTK
    gtk_init(&argc, &argv);
    QRData qrData = QRData();


    // Create a GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    GtkWidget* table = gtk_table_new(10,10,false);
    gtk_container_add(GTK_CONTAINER(window), table);

    // Create an entry buffer for manual file input
    GtkEntryBuffer *eBuffer = gtk_entry_buffer_new("filepath",-1);
    // Create a text input field
    GtkWidget* file_entry = gtk_entry_new_with_buffer(eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(file_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), file_entry, 1, 2, 2, 3, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);



    // Create a second entry buffer for manual text input
    GtkEntryBuffer *eBuffer2 = gtk_entry_buffer_new("text",-1);
    // Create a text input field
    GtkWidget* text_entry = gtk_entry_new_with_buffer(eBuffer2);
    gtk_entry_set_visibility(GTK_ENTRY(text_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), text_entry, 7, 9, 2, 3, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);


    // Create a third entry buffer for manual text input
    GtkEntryBuffer *eBuffer3 = gtk_entry_buffer_new("filename (.jpg or .png)",-1);
    // Create a text input field
    GtkWidget* filename_entry = gtk_entry_new_with_buffer(eBuffer3);
    gtk_entry_set_visibility(GTK_ENTRY(filename_entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), filename_entry, 7, 9, 3, 4, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);


    // Create three buttons
    GtkWidget *button1 = gtk_button_new_with_label("Open filepath");
    GtkWidget *button2 = gtk_button_new_with_label("Open Explorer");
    GtkWidget *button3 = gtk_button_new_with_label("Decode QR-Image");
    GtkWidget *button4 = gtk_button_new_with_label("Encode Text to QR-Image");
    
    // Create a GtkTextView widget
    GtkWidget* textview = gtk_text_view_new();

    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_table_attach(GTK_TABLE(table), textview, 1, 7, 3, 5, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);

    //Setting qrData variables
    qrData.set_file_entry(file_entry);
    qrData.set_textfield(textview);
    qrData.set_text_entry(text_entry);
    qrData.set_filename_entry(filename_entry);

    // Connect the "button1" signal to the signal handler
    g_signal_connect(button1, "clicked", G_CALLBACK(file_entry_button_clicked), &qrData);

    // Connect button click event handlers
    g_signal_connect(button2, "clicked", G_CALLBACK(open_filebrowser), &qrData);
    g_signal_connect(button3, "clicked", G_CALLBACK(decode_button_clicked), &qrData);
    g_signal_connect(button4, "clicked", G_CALLBACK(encode_button_clicked), &qrData);

    // Pack buttons into the vertical box
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    gtk_table_attach(GTK_TABLE(table), button2, 3, 5, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    gtk_table_attach(GTK_TABLE(table), button3, 5, 7, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    gtk_table_attach(GTK_TABLE(table), button4, 7, 9, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
 
    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();


    return 0;


}
