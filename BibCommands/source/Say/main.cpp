#include <iostream>



int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "say: expected at least 1 argument {text: string}";
        return 1;
    } else if (argc > 2) {
        std::cout << "say: too many arguments";
        return 1;
    }

    std::cout << argv[1] << std::endl;

    return 0;
}