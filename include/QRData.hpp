#include <string>
#include <gtk/gtk.h>

struct QRData
{

private:
    // filepath that has been inserted to decode an image
    std::string input_filepath;
    // filepath to write the encoded image into
    std::string output_filepath;
    // text that has been decoded from an image
    std::string decoded_text;
    // entry widget that is used to input the filepath to the decode an image
    GtkWidget *input_filepath_entry;
    // entry widget that is used to output the result of the decoder
    GtkWidget *output_decoder_entry;
    // entry widget that is used to input the text that is going to be encoded into an QRCode
    GtkWidget *input_text_encoder_entry;
    // entry widget that is used to input the filename of the resulting image from the encoder
    GtkWidget *filename_entry;
    // entry widget that is used to input the filepath where the encoder should save the generated image
    GtkWidget *output_filepath_entry;
    // textview widget that is used to output various messages like errors and suchF
    GtkWidget *message_log_textview;

public:
    void set_input_filepath(const std::string &filename);
    std::string get_input_filepath();

    void set_output_filepath(const std::string &filepath);
    std::string get_output_filepath();

    void set_decoded_text(const std::string &text);
    std::string get_decoded_text();

    void set_input_filepath_entry(GtkWidget *NewEntry);
    GtkWidget *get_input_filepath_entry();

    void set_output_decoder_entry(GtkWidget *NewEntry);
    GtkWidget *get_output_decoder_entry();

    void set_input_text_encoder_entry(GtkWidget *NewEntry);
    GtkWidget *get_input_text_encoder_entry();

    void set_filename_entry(GtkWidget *NewEntry);
    GtkWidget *get_filename_entry();

    void set_output_filepath_entry(GtkWidget *NewEntry);
    GtkWidget *get_output_filepath_entry();

    void set_message_log_textview(GtkWidget *NewEntry);
    GtkWidget *get_message_log_textview();
};
