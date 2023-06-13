#include <string>
#include <gtk/gtk.h>

struct QRData
{

private:
    std::string input_filepath;
    std::string decoded_text;
    GtkWidget *input_filepath_textfield;
    GtkWidget *textfield;
    GtkWidget *input_text_encoder_entry;
    GtkWidget *filename_entry;

public:
    void set_input_filepath(const std::string &filename);
    std::string get_input_filepath();

    void set_decoded_text(const std::string &text);
    std::string get_decoded_text();

    void set_input_filepath_textfield(GtkWidget *NewEntry);
    GtkWidget *get_input_filepath_textfield();

    void set_output_decoder_textfield(GtkWidget *NewTextfield);
    GtkWidget *get_output_decoder_textfield();

    void set_input_text_encoder_entry(GtkWidget *NewEntry);
    GtkWidget *get_input_text_encoder_entry();

    void set_filename_entry(GtkWidget *NewEntry);
    GtkWidget *get_filename_entry();
};
