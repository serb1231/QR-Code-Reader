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

void QRData::set_entry(GtkWidget* NewEntry)
{
    QRData::entry = NewEntry;
}

GtkWidget* QRData::get_entry()
{
    return QRData::entry;
}
