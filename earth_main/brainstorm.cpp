//  brainstorm.cpp

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <map>
#include <string>
#include <chrono>
#include <thread>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#include "brainstorm.h"
using namespace std;

// Function to pause the file output until press Enter
static void pause() {
    cin.get();
}

// Function to pause the program for a while
static void sleep() {
    this_thread::sleep_for(chrono::milliseconds(1000));
}

// Function to deal with invalid input
static void issueWarning() {
    cout << BOLD << RED << "\nInvalid input. Pls input again!" << RESET << endl;
}

// Function to print lines in a certain range
void printLine (string file_name, int line_start, int line_end, int effect_start, int effect_end, string special_effect) {
    ifstream fin;
    string line;
    int line_count = 1;
    fin.open(file_name);
    if (fin.fail()) {
        exit(1);
    }
    else {
        while (getline(fin, line)) {
            if (line_count >= line_start && line_count <= line_end) {
                if (line_count >= effect_start && line_count <= effect_end) {
                    if (special_effect == "underline") {
                        pause();
                        cout << BOLD << UNDERLINE << line << RESET;
                    }
                    else if (special_effect == "italic") {
                        pause();
                        cout << BOLD << ITALIC << line << RESET;
                    }
                    else {
                        pause();
                        cout << BOLD << line << RESET;
                    }
                }
                else {
                    pause();
                    cout << line;
                }
            }
            line_count++;
        }
        cout << "\n";
        fin.close();
    }
}

// Function to randomly select question index
void generateIndex(int n, int lower_bound, int upper_bound, int arr[4]) {
    srand(time(0));
    for (int i = 0; i < n; i++) {
        int num = rand() % (upper_bound - lower_bound + 1) + lower_bound;
        while (true) {
            bool isRepeat = false;
            for (int j = 0; j < i; j++) {
                if (arr[j] == num) {
                    isRepeat = true;
                    break;
                }
            }
            if (isRepeat) {
                num = rand() % (upper_bound - lower_bound + 1) + lower_bound;
            }
            else {
                break;
            }
        }
        arr[i] = num;
    }
}

// Fuction to play easy mode
bool runEasyGame() {
    string solution, answer;
    int attemp_count;
    int problem_index[4];
    char surrender;
    generateIndex(4, 1, 10, problem_index);
    cout << "\nAlien: Prepare to be tested by me, cowardly human." << endl;
    for (int i = 0; i < 4; i++) {
        attemp_count = 0;
        sleep();
        pause();
        cout << BOLD << BLUE << "\nQuestion " << i+1 << RESET << endl;
        cout << "(Press Enter to continue)" << endl;
        if (problem_index[i] == 10) {
            printLine("ch6_script.txt", 13, 17, 13, 17, "italic");
            solution = "MUSIC";
        }
        else if (problem_index[i] == 9) {
            printLine("ch6_script.txt", 23, 27, 23, 27, "italic");
            solution = "FUTURE";
        }
        else if (problem_index[i] == 8) {
            printLine("ch6_script.txt", 33, 38, 33, 38, "italic");
            solution = "TIME";
        }
        else if (problem_index[i] == 7) {
            printLine("ch6_script.txt", 44, 48, 44, 48, "italic");
            solution = "CANDLE";
        }
        else if (problem_index[i] == 6) {
            printLine("ch6_script.txt", 54, 58, 54, 58, "italic");
            solution = "ECHO";
        }
        else if (problem_index[i] == 5) {
            printLine("ch6_script.txt", 64, 64, 64, 64, "italic");
            solution = "ENVELOPE";
        }
        else if (problem_index[i] == 4) {
            printLine("ch6_script.txt", 70, 70, 70, 70, "italic");
            solution = "TEAPOT";
        }
        else if (problem_index[i] == 3) {
            printLine("ch6_script.txt", 76, 76, 76, 76, "italic");
            solution = "SHORT";
        }
        else if (problem_index[i] == 2) {
            printLine("ch6_script.txt", 82, 82, 82, 82, "italic");
            solution = "WHOLESOME";
        }
        else {
            printLine("ch6_script.txt", 88, 88, 88, 88, "italic");
            solution = "SEVEN";
        }
        sleep();
        cout << "\nPls input your answer in uppercase, e.g., \"APPLE\", after thinking carefully." << RESET << endl;
        while (attemp_count < 3) {
            cin >> answer;
            if (answer == solution) {
                cout << BOLD << GREEN << "\nCorrect!" << RESET << endl;
                cout << "Alien: Well, seems that you're not that stupid." << endl;
                break;
            }
            else {
                cout << BOLD << RED << "\nWrong!" << RESET << endl;
                if (attemp_count < 2) {
                    sleep();
                    cout << "Pls input again." << RESET << endl;
                }
            }
            attemp_count++;
        }
        if (answer != solution) {
            sleep();
            cout << "\nAlien: You have guessed wrongly for three times. As I expected, humans are really stupid creatures. \nIf you admit that you are stupid, I may just let you pass this puzzle. HAHAHAHAHAHAHAHA..." << endl;
            sleep();
            cout << "\nPls input Y/N for yes/no respectively." << endl;
            while (cin >> surrender) {
                if (surrender == 'Y') {
                    cout << "\nAlien: Well, modesty is also a virtue." << endl;
                    sleep();
                    cout << "The answer for this question is: " << BOLD << solution << RESET << "." << endl;
                    break;
                }
                else if (surrender == 'N') {
                    cout << BOLD << RED << "\nYou irritate the alien. You are killed immediately. Mission failed!" << RESET << endl;
                    return 0;
                }
                else {
                    issueWarning();
                }
            }
        }
    }
    return 1;
}

// Function to play hard mode
bool runHardGame() {
    string solution, answer;
    int attemp_count, problem_index;
    char hint, surrender;
    cout << "\nAlien: Wow. What an arrogant human! In that case, just wait for your death." << endl;
    // start question 1
    attemp_count = 0;
    sleep();
    pause();
    cout << BOLD << BLUE << "\nQuestion 1" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    srand(time(0));
    problem_index = rand() % 5 + 1;
    if (problem_index == 5) {
        printLine("ch6_script.txt", 97, 97, 97, 97, "bold");
        solution = "SILENCE";
    }
    else if (problem_index == 4) {
        printLine("ch6_script.txt", 103, 103, 103, 103, "bold");
        solution = "HUMAN";
    }
    else if (problem_index == 3) {
        printLine("ch6_script.txt", 109, 109, 109, 109, "bold");
        solution = "COIN";
    }
    else if (problem_index == 2) {
        printLine("ch6_script.txt", 115, 115, 115, 115, "bold");
        solution = "RIVER";
    }
    else {
        printLine("ch6_script.txt", 121, 121, 121, 121, "bold");
        solution = "BREATH";
    }
    sleep();
    cout << "\nPls input your answer in uppercase, e.g., \"APPLE\", after thinking carefully." << endl;
    while (attemp_count < 3) {
        cin >> answer;
        if (answer == solution) {
            cout << BOLD << GREEN << "\nCorrect!" << RESET << endl;
            cout << "Alien: Well, seems that you're not that stupid." << endl;
            break;
        }
        else {
            cout << BOLD << RED << "\nWrong!" << RESET << endl;
            if (attemp_count < 2) {
                sleep();
                cout << "Pls input again." << endl;
            }
        }
        attemp_count++;
    }
    if (answer != solution) {
        sleep();
        cout << "Alien: You have guessed wrongly for three times. As I expected, humans are really stupid creatures. \nIf you admit that you are stupid, I may just let you pass this puzzle. HAHAHAHAHAHAHAHA..." << endl;
        sleep();
        cout << "\nPls input Y/N for yes/no respectively." << endl;
        while (cin >> surrender) {
            if (surrender == 'Y') {
                cout << "\nAlien: Well, modesty is also a virtue." << endl;
                sleep();
                cout << "The answer for this question is: " << BOLD << solution << RESET << "." << endl;
                break;
            }
            else if (surrender == 'N') {
                cout << BOLD << RED << "\nYou irritate the alien. You are killed immediately. Mission failed!" << RESET << endl;
                return 0;
            }
            else {
                issueWarning();
            }
        }
    }
    // start question 2
    solution = "B";
    sleep();
    pause();
    cout << BOLD << BLUE << "\nQuestion 2" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    printLine("ch6_script.txt", 127, 133, 0, 0, "none");
    cout << "\nAlien: This question is a difficult one. I believe only people with wisdom can solve it. \nDo you want hint for this question?" << endl;
    sleep();
    cout << "\nPls input Y/N for yes/no respectively." << endl;
    while (cin >> hint) {
        if (hint == 'Y') {
            cout << "\nThe message is encoded by Caesar cipher with a shift of 13 letters... \n(Press Enter to continue)" << endl;
            string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
            string key = "QWERTYUIOPASDFGHJKLZXCVBNM";
            map<char, char> table;
            for (int i = 0; i < alphabet.length(); i++) {
                table[key[i]] = alphabet[i];
            }
            pause();
            pause();
            cout << "Substitution Table" << endl;
            cout << "------------------" << endl;
            for (auto itr = table.begin(); itr != table.end(); itr++) {
                cout << itr->first << "       ->       " << itr->second << endl;
            }
            cout << "\n";
            break;
        }
        else if (hint == 'N') {
            cout << "\nAlien: Good luck, arrogant human." << endl;
            break;
        }
        else {
            issueWarning();
        }
    }
    sleep();
    cout << "\nPls input the option in uppercase, e.g., 'A', after thinking carefully." << endl;
    cin >> answer;
    if (answer == solution) {
        cout << BOLD << GREEN << "\nCorrect!" << RESET << endl;
        cout << "Alien: Well, seems that you're not that stupid." << endl;
    } else {
        cout << BOLD << RED << "\nWrong!" << RESET << endl;
        cout << "Alien: I don't allow people who can make mistake in mc-question to live in the world!" << endl;
        sleep();
        cout << BOLD << RED << "\nYou irritate the alien. You are killed immediately. Mission failed!" << RESET << endl;
        return 0;
    }
    // start question 3
    attemp_count = 0;
    solution = "DICKENS";
    sleep();
    pause();
    cout << BOLD << BLUE << "\nQuestion 3" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    printLine("ch6_script.txt", 136, 139, 0, 0, "none");
    cout << "\nAlien: This question is a difficult one. I believe only people with wisdom can solve it. \nDo you want hint for this question?" << endl;
    sleep();
    cout << "\nPls input Y/N for yes/no respectively" << endl;
    while (cin >> hint) {
        if (hint == 'Y') {
            map<char, string> morseMap = {
                {'A', ".-"}, {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},
                {'E', "."}, {'F', "..-."}, {'G', "--."}, {'H', "...."},
                {'I', ".."}, {'J', ".---"}, {'K', "-.-"}, {'L', ".-.."},
                {'M', "--"}, {'N', "-."}, {'O', "---"}, {'P', ".--."},
                {'Q', "--.-"}, {'R', ".-."}, {'S', "..."}, {'T', "-"},
                {'U', "..-"}, {'V', "...-"}, {'W', ".--"}, {'X', "-..-"},
                {'Y', "-.--"}, {'Z', "--.."}
            };
            cout << "\nThe message is encoded in Morse code. \n(Press Enter to continue)"  << endl;
            pause();
            pause();
            cout << "Letter   Morse Code" << endl;
            cout << "------   ----------" << endl;
            for (auto itr = morseMap.begin(); itr != morseMap.end(); itr++) {
                cout << itr->first << "        " << itr->second << endl;
            }
            cout << "\n";
            break;
        }
        else if (hint == 'N') {
            cout << "\nAlien: Good luck, arrogant human." << endl;
            break;
        }
        else {
            issueWarning();
        }
    }
    sleep();
    cout <<  "\nPls input the seven-digit password in uppercase, e.g., \"ABCDEFG\", after thinking carefully." << endl;
    while (attemp_count < 3) {
        cin >> answer;
        if (answer == solution) {
            cout << BOLD << GREEN << "\nCorrect!" << RESET << endl;
            cout << "Alien: Well, seems that you're not that stupid." << endl;
            break;
        }
        else {
            cout << BOLD << RED << "\nWrong!" << RESET << endl;
            if (attemp_count < 2) {
                sleep();
                sleep();
                cout << "Pls input again." << endl;
            }
        }
        attemp_count++;
    }
    if (answer != solution) {
        sleep();
        cout << "\nAlien: You have guessed wrongly for three times. As I expected, humans are really stupid creatures. \nIf you admit that you are stupid, I may just let you pass this puzzle. HAHAHAHAHAHAHAHA..." << endl;
        sleep();
        cout << "\nPls input Y/N for yes/no respectively." << endl;
        while (cin >> surrender) {
            if (surrender == 'Y') {
                cout << "\nAlien: Well, modesty is also a virtue." << endl;
                sleep();
                cout << "The answer for this question is: " << BOLD << solution << RESET << "." << endl;
                break;
            }
            else if (surrender == 'N') {
                cout << BOLD << RED << "\nYou irritate the alien. You are killed immediately. Mission failed!" << RESET << endl;
                return 0;
            }
            else {
                issueWarning();
            }
        }
    }
    // start question 4
    sleep();
    pause();
    cout << BOLD << BLUE << "\nQuestion 4" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    srand(time(0));
    problem_index = rand() % 5 + 1;
    if (problem_index == 1) {
        printLine("ch6_script.txt", 148, 167, 0, 0, "none");
        solution = "B";
    }
    else if (problem_index == 2) {
        printLine("ch6_script.txt", 173, 179, 0, 0, "none");
        solution = "B";
    }
    else if (problem_index == 3) {
        printLine("ch6_script.txt", 185, 194, 0, 0, "none");
        solution = "C";
    }
    else if (problem_index == 4) {
        printLine("ch6_script.txt", 200, 208, 0, 0, "none");
        solution = "B";
    }
    else {
        printLine("ch6_script.txt", 214, 221, 0, 0, "none");
        solution = "A";
    }
    sleep();
    cout << "\nPls input the option in uppercase, e.g., 'A', after thinking carefully." << endl;
    cin >> answer;
    if (answer == solution) {
        cout << BOLD << GREEN << "\nCorrect!" << RESET << endl;
        cout << "Alien: Well, it seems that you're not that stupid." << endl;
    } else {
        cout << BOLD << RED << "\nWrong!" << RESET << endl;
        cout << "Alien: I don't allow people who can make mistake in mc-question to live in the world!" << endl;
        sleep();
        cout << BOLD << RED << "\nYou irritate the alien. You are killed immediately. Mission failed!" << RESET << endl;
        return 0;
    }
    return 1;
}

// Function to play the complete story
bool playBrainstorm() {
    char difficulty;
    bool game_pass = false;
    sleep();
    cout << BLUE << BOLD << "\nGame Rule" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    pause();
    cout << "1. You need to solve four brain-teaser questions (randomly selected from a problem bank) to pass the game.";
    pause();
    cout << "- For multiple-choice questions, there will only be one chance to answer.";
    pause();
    cout << "- Non multiple-choices questions allow you to reponse for up to three times.";
    pause();
    cout << "2. You will be given a chance to jump a question after you answer wrongly for three times.";
    pause();
    cout << "3. You can choose either \"Easy\" or \"Hard\" mode at the beginning. \nYou pass the game as long as you answer four questions correctly, no matter of which mode you choose.";
    pause();
    cout << BOLD << "4. All user inputs in this game should be in upper case!" << RESET;
    pause();
    cout << "\nAn alien suddenly appears on the screen..." << endl;
    string alien_picture = R"(
         .-^-.
        /_/_\_\
        ' ' | `
         |_|_|
        /_/_\_\
       // //\\
      || || ||||
      || || ||||
      \\ \\//
       `'''`
       )";
    pause();
    cout << alien_picture << endl;
    printLine("ch6_script.txt", 2, 5, 0, 0, "none");
    sleep();
    cout << "\nPls choose the difficulty: input E/H for easy/hard respectively." << endl;
    while (cin >> difficulty) {
        if (difficulty == 'E') {
            game_pass = runEasyGame();
            break;
        }
        else if (difficulty == 'H') {
            game_pass = runHardGame();
            break;
        }
        else {
            issueWarning();
        }
    }
    if (game_pass) {
        sleep();
        cout << "\nAlien: I admit that you're a smart guy. You passed my test, now you can go." << endl;
        cout << GREEN << BOLD << "Mission Succeed!" << RESET << endl;
        return 1;
    }
    else {
        return 0;
    }
}
