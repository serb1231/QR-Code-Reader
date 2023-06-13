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

void QRData::set_file_entry(GtkWidget* NewEntry)
{
    QRData::file_entry = NewEntry;
}

GtkWidget* QRData::get_file_entry()
{
    return QRData::file_entry;
}

void QRData::set_textfield(GtkWidget* NewTextfield)
{
    QRData::textfield = NewTextfield;
}

GtkWidget* QRData::get_textfield()
{
    return QRData::textfield;
}

void QRData::set_text_entry(GtkWidget* NewEntry)
{
    QRData::text_entry = NewEntry;
}

GtkWidget* QRData::get_text_entry()
{
    return QRData::text_entry;
}

void QRData::set_filename_entry(GtkWidget* NewEntry)
{
    QRData::filename_entry = NewEntry;
}

GtkWidget* QRData::get_filename_entry()
{
    return QRData::filename_entry;
}