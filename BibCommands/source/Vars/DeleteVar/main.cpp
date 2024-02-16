#include <iostream>
#include <fstream>
#include <string>
#include <cstring>


#ifdef __linux__
    #include <unistd.h>
    #define OS_SEPARATATOR '/'
#elif _WIN32
    #include <windows.h>
    #define OS_SEPARATATOR '\\'
#else
    #error "Platform not Compatible"
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

void usualOperation(std::string var, std::string file) {
    std::ifstream ifs(file);
    std::string text = "";

    if (ifs.is_open()) {
        std::string line = "";
        int count = 0; 
        
        do {
            std::string name = line.substr(0, line.find(":"));
            
            ++count;
			if (name != var) {
				text += line;
				if (count != 1) text += "\n";
			}
            
        } while(std::getline(ifs, line));
    } else {
		std::cout << "ERROR" << std::endl;
	}
	ifs.close();
    std::ofstream ofs(file);

    if (ofs.is_open()) {
        ofs << text << std::endl;;
        ofs.close();
    }
}


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "delvar: expected at least 1 argument {operation: (-)string, (optional)[var: string]}" << std::endl;
        return 1;
    } else if (argc > 3) {
		std::cout << "delvar: too many arguments" << std::endl;
	}

    if (std::string(argv[1]) == "-usual") {
        std::string var = argv[2];
        
        usualOperation(var, getPath());
    } else {
		std::cout << "Temporal Error" << std::endl;
	}

    return 0;
}
