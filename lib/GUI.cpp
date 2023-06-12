#include <gtk/gtk.h>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <GtkFileExplorer.hpp>

#define STD_PADDING 5

void open_image(const std::string& path){

        // Displaying Image
        cv::Mat image;
        image = cv::imread(path, 1);

        if (!image.data)
        {
            printf("Seleced File was not an image \n");
        
        }

        cv::namedWindow("Selected Image:", cv::WINDOW_AUTOSIZE);
        cv::imshow("Selected Image:", image);
        cv::waitKey(0);

}


// Button click event handler
void button_clicked(GtkWidget *widget, gpointer user_data)
{
    g_print("Button clicked!\n");
}

// Enter Key event handler
static void entry_activate_callback(GtkEntry* entry, gpointer user_data) {
        std::cout << gtk_entry_get_text(GTK_ENTRY(entry)) << std::endl;
}

void entry_button_clicked(GtkWidget* widget, GtkEntry* entry, gpointer user_data) {
    g_print("You entered: ");
    std::cout << gtk_entry_get_text(GTK_ENTRY(entry)) << std::endl;
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

    GtkFileExplorer *data = static_cast<GtkFileExplorer *>(user_data);


    gint result = gtk_dialog_run(GTK_DIALOG(dialog));
    if (result == GTK_RESPONSE_ACCEPT) {
        char* filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));

        open_image(filename);

        g_print("Selected file:%s\n",filename);

    }else{
        g_print("File selection canceled by the user\n");
    }

    gtk_widget_destroy(dialog);
}


int gui_handler(int argc, char** argv) {

// Initialize GTK
    gtk_init(&argc, &argv);

    // Create a GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a vertical box container
    GtkWidget* table = gtk_table_new(10,10,false);
    gtk_container_add(GTK_CONTAINER(window), table);

    // Create an entry buffer
    GtkEntryBuffer *eBuffer = gtk_entry_buffer_new("filepath",-1);
    // Create a text input field
    GtkWidget* entry = gtk_entry_new_with_buffer(eBuffer);
    gtk_entry_set_visibility(GTK_ENTRY(entry), TRUE);
    gtk_table_attach(GTK_TABLE(table), entry, 1, 2, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);


    // Create three buttons
    GtkWidget *button1 = gtk_button_new_with_label("accept");
    GtkWidget *button2 = gtk_button_new_with_label("browse");
    GtkWidget *button3 = gtk_button_new_with_label("Button 3");

    // Connect the "button1" signal to the signal handler
    g_signal_connect(button1, "clicked", G_CALLBACK(entry_button_clicked), entry);

    // Connect button click event handlers
    g_signal_connect(button2, "clicked", G_CALLBACK(open_filebrowser), NULL);
    g_signal_connect(button3, "clicked", G_CALLBACK(button_clicked), NULL);

    // Pack buttons into the vertical box
    gtk_table_attach(GTK_TABLE(table), button1, 1, 2, 2, 3, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    gtk_table_attach(GTK_TABLE(table), button2, 3, 5, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
    gtk_table_attach(GTK_TABLE(table), button3, 5, 7, 1, 2, GTK_FILL, GTK_FILL, STD_PADDING, STD_PADDING);
 
    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();


    return 0;


}
