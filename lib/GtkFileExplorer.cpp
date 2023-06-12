#include "GtkFileExplorer.hpp"

void GtkFileExplorer::setFile(const std::string &filename)
{
    GtkFileExplorer::file = filename;
}

std::string GtkFileExplorer::getFile()
{
    return GtkFileExplorer::file;
}