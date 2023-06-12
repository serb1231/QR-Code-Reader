#include <string>

struct GtkFileExplorer{

    private:
        static std::string file;
        
    public:
        static void setFile(const std::string& filename);
        static std::string getFile();
};

//static variable need to be initialised
std::string GtkFileExplorer::file = "";