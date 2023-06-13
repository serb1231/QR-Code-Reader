#include <gtk/gtk.h>

// Callback function to handle the button click event
void on_button_clicked(GtkButton* button, gpointer user_data) {
    // Get the GtkTextView widget from the user data
    GtkTextView* textview = GTK_TEXT_VIEW(user_data);

    // Get the GtkTextBuffer associated with the textview
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(textview);

    // Get the start and end iterators of the buffer
    GtkTextIter start, end;
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    // Insert the text at the end of the buffer
    gtk_text_buffer_insert(buffer, &end, "Hello, world!\n", -1);
}

int main(int argc, char* argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new GtkWindow
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text Output Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 200, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a GtkTextView widget
    GtkWidget* textview = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(textview), FALSE);

    // Create a button to output text
    GtkWidget* button = gtk_button_new_with_label("Output Text");
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), textview);

    // Create a vertical box to hold the widgets
    GtkWidget* vbox = gtk_vbox_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_box_pack_start(GTK_BOX(vbox), textview, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Add the vbox to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Show all the widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}