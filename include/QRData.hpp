#include <string>
#include <gtk/gtk.h>


struct QRData{

    private:
        std::string input_filepath;
        std::string decoded_text;
        GtkWidget* file_entry;
        GtkWidget* textfield;
        GtkWidget* text_entry;
        
    public:
        void set_input_filepath(const std::string& filename);
        std::string get_input_filepath();

        void set_decoded_text(const std::string& text);
        std::string get_decoded_text();

        void set_file_entry(GtkWidget* NewEntry);
        GtkWidget* get_file_entry();

        void set_textfield(GtkWidget* NewTextfield);
        GtkWidget* get_textfield();

        void set_text_entry(GtkWidget* NewEntry);
        GtkWidget* get_text_entry();
};
