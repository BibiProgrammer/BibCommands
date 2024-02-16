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

void usualOperation(char **vars, std::string file) {
    std::ifstream ifs(file);
    std::string text = "";

    if (ifs.is_open()) {
        std::string line;
        do {
            std::string name = line.substr(0, line.find(":"));
            std::cout << name << std::endl;
            
            for (int i = 0; i < sizeof(vars); ++i) {
				if (name != vars[i]) {
					text += line + "\n";
					std::cout << i << std::endl;
				}
			}
            
        } while(std::getline(ifs, line));
    } else {
		std::cout << "ERROR" << std::endl;
	}

    std::ofstream ofs(file);

    if (ofs.is_open()) {
        ofs << text << std::endl;;
    }
}


int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "delvar: expected at least 1 argument {operation: (-)string, (optional)[vars: strings]}" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "-usual") {
        char *vars[256] = {''};
        
        for (int i = 0; i < sizeof(argv+2); ++i) {
			vars[i] = argv[i+2];
		}
        
        usualOperation(vars, getPath());
    } else {
		std::cout << argv[1] << std::endl;
	}

    return 0;
}
