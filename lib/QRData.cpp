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
    QRData::textfield = NewTextfield;
}

GtkWidget *QRData::get_output_decoder_textfield()
{
    return QRData::textfield;
}

void QRData::set_input_text_encoder_entry(GtkWidget *NewEntry)
{
    QRData::input_text_encoder_entry = NewEntry;
}

GtkWidget *QRData::get_input_text_encoder_entry()
{
    return QRData::input_text_encoder_entry;
}

void QRData::set_filename_entry(GtkWidget *NewEntry)
{
    QRData::filename_entry = NewEntry;
}

GtkWidget *QRData::get_filename_entry()
{
    return QRData::filename_entry;
}

void QRData::set_message_log_textview(GtkWidget *NewMessageLogTextview)
{
    QRData::message_log_textview = NewMessageLogTextview;
}

GtkWidget *QRData::get_message_log_textview()
{
    return QRData::message_log_textview;
}