#include <string>

struct GtkFileExplorer{

    private:
        std::string file;
        
    public:
        void setFile(const std::string& filename);
        std::string getFile();
};

//static variable need to be initialised
//std::string GtkFileExplorer::file = "";