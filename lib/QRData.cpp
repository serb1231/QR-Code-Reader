#include "QRData.hpp"

void QRData::set_input_filepath(const std::string &filename)
{
    QRData::input_filepath = filename;
}

std::string QRData::get_input_filepath()
{
    return QRData::input_filepath;
}

void QRData::set_decoded_text(const std::string &text)
{
    QRData::decoded_text = text;
}

std::string QRData::get_decoded_text()
{
    return QRData::decoded_text;
}

void QRData::set_input_filepath_textfield(GtkWidget *NewEntry)
{
    QRData::input_filepath_textfield = NewEntry;
}

GtkWidget *QRData::get_input_filepath_textfield()
{
    return QRData::input_filepath_textfield;
}

void QRData::set_output_decoder_textfield(GtkWidget *NewTextfield)
{
    QRData::output_decoder_textfield = NewTextfield;
}

GtkWidget *QRData::get_output_decoder_textfield()
{
    return QRData::output_decoder_textfield;
}

void QRData::set_image_widget(GtkWidget *new_image_widget)
{
    QRData::image_widget = new_image_widget;
}

GtkWidget *QRData::get_image_widget()
{
    return QRData::image_widget;
}