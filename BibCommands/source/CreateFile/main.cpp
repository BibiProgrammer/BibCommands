#include <iostream>
#include <fstream>


int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "crtdoc: expected at least 1 argument {ubication: string}, {(optional) content: string}";
        return 1;
    } else if (argc > 3) {
        std::cout << "crtdoc: too many arguments";
    }


    std::string ubication = argv[1];

    std::ofstream file(ubication);
    
    if (argc > 2) {
        file << argv[2];
    }
    file.close();

    return 0;
}