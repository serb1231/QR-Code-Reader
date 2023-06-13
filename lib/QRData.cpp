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
    QRData::entry = NewEntry;
}

GtkWidget* QRData::get_entry()
{
    return QRData::entry;
}

void QRData::set_textfield(GtkWidget* NewTextfield)
{
    QRData::textfield = NewTextfield;
}

GtkWidget* QRData::get_textfield()
{
    return QRData::image_widget;
}

void QRData::set_text_entry(GtkWidget* NewEntry)
{
    QRData::text_entry = NewEntry;
}

GtkWidget* QRData::get_text_entry()
{
    return QRData::text_entry;
}