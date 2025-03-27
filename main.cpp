#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
using std::string, std::vector, std::cout, std::cin;


/*=======Settings=======*/
const string PATH {"../SPANISH_EASY.txt"}; 
// Change this to the path of your words database file. 
// The path should be relative to the output file (executable), no to the main.cpp file.

const int MAX_TRIES {6}; 
// You can change the maximum number of tries.

const int WORD_LENGTH {5}; 
// You can change the word length. 

const string ALLOWED_CHARACTERS = 
{"abcdefghijklmnñopqrstuvwxyz" "ABCDEFGHIJKLMNÑOPQRSTUVWXYZ" "-"}; 
// You can change the allowed characters too, but this is Wordle so it's not recommended. 
// For any reason don't put spaces in the string. 

namespace color { 
// Do not change this values unless you are colorblind 
// or something like that (just don't change it).

    constexpr char rst[] = "\033[0m"; // Reset 
    constexpr char rd[] = "\033[31m"; // Red
    constexpr char gn[] = "\033[32m"; // Green
    constexpr char yl[] = "\033[33m"; // Yellow
}


// Early declarations:
int get_lines_count(string file_path);
string get_word(int word_count);
void loop(string word);


// Main function
int main () {
    cout << color::yl << "Welcome to Wordle!" << '\n';
    cout << "Press Enter to start..." << color::rst << '\n';
    cin.ignore();
    int lines_count = get_lines_count(PATH);
    string word = get_word(lines_count);

    // Debug lines :
    // cout << "Lines count:" << lines_count << " Word: " << word << '\n';
    // cin.ignore();

    loop(word);

    return 0;
}


/*==========================DEFINITIONS=================================*/

int rand_int(int max){
// This function was stolen from chatGPT. I don't know how it works but it works.
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> distribution(0, max);
    int ran = distribution(generator);
    return ran; // It returns a random integer between 0 and max.
}

int get_lines_count(string file_path){ 
// Counts the number of lines in the file in order to get a random word.  
    int count = 0;
    string word;
    std::ifstream file(file_path);

    if(file.is_open()){ 
        while (getline(file, word)){ 
        // It iterates through all lines in the text file, 
        // using the get_line function, counting the number of words.
            
            count++;
        }
    }

    file.close();
    return count;
}

string get_line(int id){ // Get a specific line from the text file.
    string word;
    std::ifstream file(PATH);

    if(file.is_open()){
        for(int i = 0; i < id; i++){
            getline(file, word); // It gets lines until the line number is reached.
        }
    }

    file.close();
    return word;
}

bool is_word_in_file(string word, string PATH){ 
// Function that checks if the word is in the file.
    std::ifstream file(PATH);
    string line;
    while (getline(file, line)) {
        if (line == word) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

bool valid_word(string word){ // Valid the word.
    if (word.length() != WORD_LENGTH) { 
        return false; 
    } // Word have to be a fixed length.

    for (int i = 0; i < WORD_LENGTH; i++) { 
        if (ALLOWED_CHARACTERS.find(word[i]) == string::npos) { return false; } // Word can only contain letters
    }

    return true;
}

string get_word (int word_count) { 
// Function that handle the process of gathering and 
// verification of words from the text file.
    string word = "";
    while (valid_word(word) == false) {
        word = get_line(rand_int(word_count));
    }
    return word;
}

void format (string input, string correct_word) { 
// Print one word, letters will have different colors.
    for (int i = 0; i < static_cast<int>(input.length()); i++) {
        if (input[i] == correct_word[i]) {
            cout << color::gn << input[i] << color::rst;
        } else if (correct_word.find(input[i]) != string::npos) {
            cout << color::yl << input[i] << color::rst;
        } else {
            cout << input[i];
        }
    }
    cout << '\n';
};

void print_tries (std::vector<string>& tries, string& correct_word){  
// Prints each word that the player has guessed, each letter will get a color 
// depending on if it is correct or not and in what position it is.
    system("clear");  
    for (auto _try : tries){
        format(_try, correct_word);
    }
}

void loop (string word){ // Main loop of the game 
    vector<string> tries = {};
    string input = "";

    for (int i = 0; i < MAX_TRIES; i++) {
        input = "";
        while (is_word_in_file(input, PATH) == false || valid_word(input) == false) {
            print_tries(tries, word);
            cout << "> ";
            cin >> input;
        }
        tries.push_back(input);

        if (input == word) {
            print_tries(tries, word);
            cout << color::gn << "The word was: " << word << '\n';
            cout << "You Won!" << color::rst << '\n';
            return;
        } 
    }

    print_tries(tries, word);
    cout  << color::rd << "The word was: " << word << '\n';
    cout << "You Lost!"  << color::rst << '\n';
    return;
}