#include <iostream>
#include <fstream>
#include <string>


#ifdef __linux__
    #include <unistd.h>
    #define OS_SEPARATATOR "/"
#elif _WIN32
    #include <windows.h>
    #define OS_SEPARATATOR "\\"
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



void createVar(const std::string &file, const std::string &var_name, const std::string &var_value) {
    std::ifstream ifs(file);
    bool replace = false;
    std::string text;

    if (ifs.is_open()) {
        std::string line;

        do {
            std::string name, value;

            name = line.substr(0, line.find(":"));

            if (name == var_name) {
                line = var_name + ":" + var_value;
                replace = true;
            }

            if (!text.empty()) text += "\n";

            text += line;

        } while(std::getline(ifs, line));
    }

    if (!replace) {
        std::ofstream add(file, std::ios::app);
        if (add.is_open()) {
            add << var_name + ":" + var_value << std::endl;
            add.close();
        } else {
            std::cout << R"(ERROR TRYING TO OPEN '00_vars.txt', YOU CAN FIX IT MANUALLY IN '~\Documents\BibCommands\uservars (for windows)  user/.config/BibCommands/uservars (for linux)' )" << std::endl;
        }
    } else {
        std::ofstream repl(file);
        if (repl.is_open()) {
            repl << text;
            repl.close();
        } else {
            std::cout << R"(ERROR TRYING TO OPEN '00_vars.txt', YOU CAN FIX IT MANUALLY IN '~\Documents\BibCommands\uservars (for windows)  user/.config/BibCommands/uservars (for linux)' )" << std::endl;
        }
    }
}


int main(int argc, char **argv) {
    if (argc < 3) {
        std::cout << "setvar: expected at least 2 arguments {var_name: string, var_value: unknown type}" << std::endl;
        return 1;
    } else if (argc > 3) {
        std::cout << "setvar: too arguments";
        return 1;
    }

    std::string file = getPath();
    std::string var_name = argv[1];
    std::string var_value = argv[2];
    createVar(file, var_name, var_value);

    return 0;
}