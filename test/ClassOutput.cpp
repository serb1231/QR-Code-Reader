#include <gtk/gtk.h>

// Signal handler function for the button's "clicked" signal
void on_button_clicked(GtkWidget* button, gpointer data) {
    // Cast the data pointer to a GtkTextView pointer
    GtkTextView* textview = GTK_TEXT_VIEW(data);

    // Get the GtkTextBuffer of the textview
    GtkTextBuffer* buffer = gtk_text_view_get_buffer(textview);

    // Clear the existing text in the buffer
    gtk_text_buffer_set_text(buffer, "", -1);

    // Insert the new text into the buffer
    const gchar* new_text = "New Text";
    gtk_text_buffer_insert_at_cursor(buffer, new_text, -1);
}

int main(int argc, char* argv[]) {
    // Initialize GTK
    gtk_init(&argc, &argv);

    // Create a new GtkWindow
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text Output Example");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create a GtkTextView widget
    GtkWidget* textview = gtk_text_view_new();

    // Create a GtkButton widget
    GtkWidget* button = gtk_button_new_with_label("Click me!");

    // Connect the "clicked" signal of the button to the signal handler function
    g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), textview);

    // Create a GtkScrolledWindow to hold the textview
    GtkWidget* scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(scrolled_window),
                                   GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);
    gtk_container_add(GTK_CONTAINER(scrolled_window), textview);

    // Set the size of the scrolled window
    gtk_widget_set_size_request(scrolled_window, 200, 50);

    // Create a GtkBox to hold the scrolled window and button
    GtkWidget* vbox = gtk_vbox_new(FALSE, 10);
    gtk_box_pack_start(GTK_BOX(vbox), scrolled_window, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), button, FALSE, FALSE, 0);

    // Add the vbox to the window
    gtk_container_add(GTK_CONTAINER(window), vbox);

    // Show the vbox and window
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();

    return 0;
}
