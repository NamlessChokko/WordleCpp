#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

const std::string target = "";
const std::string output = "../formatted.txt";

int main() {
    std::ifstream inputFile(target);
    std::ofstream outputFile(output);

    if (!inputFile || !outputFile) {
        std::cerr << "There was an error opening the files. Check if they exist." << std::endl;
        return 1;
    }

    std::string word;
    while (inputFile >> word) {
        outputFile << word << '\n';  
    }

    inputFile.close();
    outputFile.close();

    std::cout << "Formatting complete. Check " << output << "." << std::endl;
    return 0;
}
