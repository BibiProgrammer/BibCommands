#include <iostream>
#include <fstream>
#include <string>


#ifdef __linux__
    #include <unistd.h>
    #define OS_SEPARATATOR '/'
#elif _WIN32
    #include <windows.h>
    #define OS_SEPARATATOR '\\'
#else
    #error "Platform not compatible"
#endif


std::string getPath() {
    std::string path;

    #ifdef __linux__
        char username[256];
        if (getlogin_r(username, sizeof(username)) == 0) {
            path = "/home/" + std::string(username) + "/.config/BibCommands/uservars/00_vars.txt";
        }
    #elif _WIN32
        char *user = getenv("username");
        path = R"(C:\Users\)" + std::string(user) + R"(\Documents\BibCommands\uservars\00_vars.txt)";
    #endif

    return path;
}


std::string getVar(std::string file, std::string var_name) {
    std::ifstream ifs(file);
    std::string value = "", line = "";

    do {
        std::string name;
        name = line.substr(0, line.find(":"));

        if (name == var_name) {
            value = line.substr(line.find(":") + 1, line.size());
            break;
        }
    } while(std::getline(ifs, line));

    if (value != "") {
        return value;
    } else {
        return "Variable not Found";
    }
}



int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "getvar: expected at least 1 argument {var_name: string}" << std::endl;
        return 1;
    } else if (argc > 2) {
        std::cout << "getvar: too arguments" << std::endl;
        return 1;
    }

    std::string file = getPath();
    std::string name = argv[1];
    std::string value = getVar(file, name);

    std::cout << value << std::endl;

    return 0;
}