#include <gtk/gtk.h>

int main (int argc,char **argv)
{
    GtkWidget *button;
    GtkWidget *window;

    gtk_init (&argc,&argv);
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    g_signal_connect (G_OBJECT(window), "destroy",
            G_CALLBACK (gtk_main_quit), NULL);

    button = gtk_button_new_with_label ("Hello World !");
    gtk_container_add (GTK_CONTAINER (window), button);

    GdkColor color;
    gdk_color_parse ("red", &color);
    gtk_widget_modify_bg (GTK_WIDGET(button), GTK_STATE_NORMAL, &color);

    gtk_widget_show_all (window);
    gtk_main ();

    return 0;
}