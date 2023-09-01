#include "wordle.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <set>

#define RESET "\033[0m"
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[1;33m"
#define BLUE "\033[1;34m"
#define CYAN "\033[1;36m"

using namespace std;

class Wordle {
	private:
        set<string> correct;
        set<string> incorrect;
        vector<string> correct_place;
        const int MAX_ATTEMPTS = 6;
        const string doc_instructions =
            "Press any key to continue.\n"
            "You have to guess the Wordle in six goes or less.\n"
            "Every word you enter must be in the word list. ...\n"
            "A correct letter turns green.\n"
            "A correct letter in the wrong place turns yellow.\n"
            "An incorrect letter turns red.\n"
            "Letters can be used more than once.\n"
            "Answers are never plurals.\n";


	vector<string> readDictionary(string filename) {
	    vector<string> words;
	    ifstream infile(filename);
	    if (infile) {
	        string word;
	        while (infile >> word) {
	            words.push_back(word);
	        }
	    }
	    return words;
	}
	
	string getRandomWord(vector<string> word_bank) {
		srand(time(NULL)); // seed the random number generator with the current time
	    int index = rand() % word_bank.size();
	    return word_bank[index];
	}
	
	bool isValidGuess(string word, string target)
{
	return (word.length() == target.length()) &&
		all_of(word.begin(), word.end(), [](char c)
		{
			return islower(c);
	});
}
	
	// Check the number of correct letters and positions in the guessed word
	void countCorrect(string guess, string target)
	{
		for (int i = 0; i < target.length(); i++)
		{
			for (int j = 0; j < guess.length(); j++)
			{
				if (guess[j] == target[i])
				{
					correct.insert(string(1, guess[j]));
					if (i == j) {
					correct_place[i] = guess[i];
					correct.erase(string(1, guess[i])); //the letter is also in the correct place so it is deleted from "correct"
					}
				}
			}
		}
	}
	
	// Check the number of correct letters (but not positions) in the guessed word
	void countIncorrect(string guess, string target)
	{
		for (int i = 0; i < guess.length(); i++)
		{
			if (target.find(guess[i]) == -1)
			{
				incorrect.insert(string(1, guess[i]));
			}
		}
	}
	void pause()
	{
		cin.get();	// read a char
	}
	//realize the blink effect
	void blink(string text, int blink_interval)
	{
		int text_length = text.length();
		for (int i = 0; i < 3; i++)
		{
			cout << text;
			fflush(stdout);	// flush the output buffer
			this_thread::sleep_for(chrono::milliseconds(blink_interval));	//show the text for blink_interval ms
			for (int j = 0; j < text_length; j++)
			{
				printf("\b \b");	// move the cursor back and print a space
				fflush(stdout);	// flush the output buffer
			}
	
			this_thread::sleep_for(chrono::milliseconds(blink_interval));	//hide the text for blink_intervalms
		}
	}
	
	//realize typer effect
	void typer_effect(string text, int delay = 40)
	{
		for (char c: text)
		{
			cout << c;
			cout.flush();
			this_thread::sleep_for(chrono::milliseconds(delay));
		}
	
		cout << endl;
	}
	
	// Print the current status of the game
	void printStatus(string guess, string target, int attempts)
	{
		countCorrect(guess, target);
		countIncorrect(guess, target);
		cout << "Guess: " << guess << endl;
		cout << "Correct Letter but Incorrect Position: ";
		for (auto it = correct.begin(); it != correct.end(); ++it)
		{
			cout << YELLOW<<*it<<RESET << " ";
		}
	
		cout << endl;
		cout << "Incorrect Letter: ";
		for (auto it = incorrect.begin(); it != incorrect.end(); ++it)
		{
			cout << RED<<*it <<RESET<< " ";
		}
	
		cout << endl;
		cout << "Current Progress: ";
		for (int i = 0; i < correct_place.size(); i++)
		{
			cout << GREEN<<correct_place[i]<<RESET << " ";
		}
	
		cout << endl;
		cout << "Attempts left: " << YELLOW<<attempts <<RESET<< endl << endl;
	}
	public:
	int init_wordle()
		{
			system("clear");
		string welcome_message = R"(
	                U  ___ u   ____     ____     _     U _____ u 
	 __        __    \/"_ \/U |  _"\ u |  _"\   |"|    \| ___"|/ 
	 \"\      /"/    | | | | \| |_) |//| | | |U | | u   |  _|"   
	 /\ \ /\ / /\.-,_| |_| |  |  _ <  U| |_| |\\| |/__  | |___   
	U  \ V  V /  U\_)-\___/   |_| \_\  |____/ u |_____| |_____|  
	.-,_\ /\ /_,-.     \\     //   \\_  |||_    //  \\  <<   >>  
	 \_)-'  '-(_/     (__)   (__)  (__)(__)_)  (_")("_)(__) (__) 
	    )";
	typer_effect(welcome_message, 4);
	string answer;
	typer_effect("Welcome to wordle!");
	cout << YELLOW << "Do you want instructions? Press 'y' for instructions and other keys to jump to the game: " << RESET << endl;
	cin >> answer;
	if (answer == "y")
	{
		for (auto &c: doc_instructions)
		{
			cout << c;
			if (c == '\n')
			{
				pause();
			}
		}
	
		system("clear");
	}
	
	// Read the dictionary file and get a random word
	vector<string> words = readDictionary("word.txt");
	vector<string> word_bank
	{
		"rocket", "cosmos", "jupiter", "travel", "ship", "space", "earth","mars","venus","star","planet","galaxy",
	};
		//define your situation-based word_bank here, words to be guessed are listed here
	string target = getRandomWord(word_bank);
	for (int i = 0; i < target.length(); i++)
	{
		correct_place.push_back("_");
	}
	
	// Print the rules of the game
	typer_effect("Welcome to Wordle! Press any key to continue");
	pause();
	cout << "Guess a " << YELLOW<<target.length()<<RESET << "-letter word using only lowercase letters." << endl;
	pause();
	cout << "You have " << YELLOW << MAX_ATTEMPTS << RESET << " attempts to guess the word." << endl << endl;
	pause();
	
	
	int attempts = MAX_ATTEMPTS;
	vector<string> correct;
	vector<string> incorrect;
	string guess;
	while (attempts > 0)
	{
		// Get a guess from the user
		cout << "Enter your guess: ";
		cin >> guess;
	
		// Check if the guess is valid
		bool in_dic = false;
		for(int i=0; i<words.size();i++){
			if(guess==words[i]){
				in_dic = true;
				break;
			}
		}
		if (!isValidGuess(guess, target) || !in_dic)
		{
			string message = "Invalid input, please try again!";
			int blink_time = 500;	// unit is milliseconds
			blink(message, blink_time);
			cout << endl << endl;
			continue;
		}
	
		// Decrement the number of attempts and print the current status of the game
		attempts--;
		printStatus(guess, target, attempts);
	
		// Check if the guess is correct
		if (guess == target)
		{
			cout << GREEN<<"Congratulations, you guessed the word! " <<RESET<< "The word was: " << YELLOW<<target<<RESET << endl;
			return 1;	//return result to the main game program to indicate whether the player has guessed out the word. Here 1 indicates winning
		}
	}
	
	// If the player has used all attempts without guessing the word, the game is over
	cout <<YELLOW<< "Sorry, you have used all your attempts." <<RESET<< endl;
	cout << "The word was: " << RED<<target<<RESET << endl;
	return 0;	// false indicates that the player has failed 
}
};

int playWordle(){
	Wordle* p_wordle = new Wordle(); //dynamic memory management
	int result = p_wordle->init_wordle();
	delete p_wordle;
	return result;
}
