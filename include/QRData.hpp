#include <string>
#include <gtk/gtk.h>

struct QRData
{

private:
    std::string input_filepath;
    std::string decoded_text;
    GtkWidget *input_filepath_textfield;
    GtkWidget *output_decoder_textfield;
    GtkWidget *image_widget;

public:
    void set_input_filepath(const std::string &new_input_filepath);
    std::string get_input_filepath();

    void set_decoded_text(const std::string &new_decoded_text);
    std::string get_decoded_text();

    void set_input_filepath_textfield(GtkWidget *new_input_filepath_textfield);
    GtkWidget *get_input_filepath_textfield();

    void set_output_decoder_textfield(GtkWidget *new_output_decoder_textfield);
    GtkWidget *get_output_decoder_textfield();

    void set_image_widget(GtkWidget *new_image_widget);
    GtkWidget *get_image_widget();
};
