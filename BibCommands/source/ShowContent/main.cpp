#include <iostream>
#include <filesystem>


namespace fs = std::filesystem;


void printFileType(const fs::path &path) {
    if (fs::is_directory(path)) {
        std::cout << "Directory: ";
    } else if (fs::is_regular_file(path)) {
        std::cout << "File: ";
    } else {
        std::cout << "UnKnow File: ";
    }
}


int main(int argc, char **argv) {

    std::string path = ".";

    if (argc == 2) {
        path = argv[1];
    } else if (argc > 2) {
        std::cout << "show: too many arguments";
        return 1;
    }

    try {
        for (const auto &entry : fs::directory_iterator(path)) {
            std::cout << entry.path().filename() << " - ";
            printFileType(entry.path());
            std::cout << "" << std::endl;
        }
    } catch (const fs::filesystem_error &ex) {
        std::cerr << "ERROR TRYING TO ACCESS DIRECTORY: " << ex.what() << std::endl; 
    }
    return 0;
}