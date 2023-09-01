#include "maze.h"
#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <time.h>
#include <fstream>

#define RESET   "\033[0m" // macro is defined to make the code easier to read
#define RED     "\033[1;31m" //ANSI color code
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define CYAN    "\033[1;36m"

using namespace std;

class MazeGame {
private: //class is used to avoid passing the vector and array manually and repetitively
    vector<string> maze;
    int status[64][64]; // record whether a single wall, which is shown as "#" should be displayed
    int visible_rounds = 15;
    int visible_size = 7;  //half the side length of visible square
    int row, col;
    int difficulty; 
	int max_time = 120; //force exit if the player is trapped for too long
public:
    MazeGame(){
        for(int i=0; i<64; i++){
            for(int j=0; j<64; j++){
                status[i][j] = 0;  //initialize the status array. everything is invisible and will be printed by " "
            }
        }
    }

    void generate_maze(int difficulty) {
        ifstream file;
        if (difficulty == 1){
            file.open("maze1.txt");
        }else{
            file.open("maze2.txt");
        }

        string line;
        if (!(file.fail())) {
            while (getline(file, line)) {
                maze.push_back(line);
            }
            file.close();
        } else {
            cout << "Unable to open maze.txt" << endl;
        }
    }

    void blink(string text, int blink_interval){ //make the text flash
        int text_length = text.length();
        for (int i = 0; i < 2; i++) {
            cout << YELLOW << text << RESET;
            fflush(stdout);
            this_thread::sleep_for(chrono::milliseconds(blink_interval));
            for (int j = 0; j < text_length; j++) {
                printf("\b \b");
                fflush(stdout);
            }
            this_thread::sleep_for(chrono::milliseconds(blink_interval));
        }
    }

    void pause() {
        cin.get();
    }

    void update_status() {
        int start_row = max(0, row - visible_size); //inside this area, the maze is shown. 
        int start_col = max(0, col - visible_size);
        int end_row = min((int)maze.size() - 1, row + visible_size);
        int end_col = min((int)maze[0].length() - 1, col + visible_size);

        for(int i=0; i<maze.size(); i++){
            for(int j=0; j<maze[i].length(); j++){
                if(!((i>=start_row && i<=end_row)&&(j>=start_col && j<=end_col)) && status[i][j]>0){ //the elements of the maze will be hidden after "visible_rounds" of rounds if they are not inside the range of the player
                    status[i][j] -= 1;
                }else if((i>=start_row && i<=end_row)&&(j>=start_col && j<=end_col)){ //maze is shown inside player's range
                    status[i][j] = visible_rounds;
                }
            }
        }
    }

    void printMaze_first_time(){
        for(int i=0; i<maze.size(); i++){
            for(int j=0; j<maze[i].length(); j++){
                if (maze[i][j]=='X'){
                    blink("X",200);
                    blink("You are Here!!!!",600); //help player find where he/she is
                    cout << "X";
                }else if(status[i][j]>0){
                    cout << maze[i][j];
                }
                else{
                    cout<<" ";
                }
            }
            cout << endl;
        }
    }

    void printMaze() {
        for(int i=0; i<maze.size(); i++){
            for(int j=0; j<maze[i].length(); j++){
            	if (status[i][j]>0){ //only elements will status>0 will be shown
			   
   			cout << maze[i][j];}else{
		   	cout<<" ";
		   }
		   }
		   
		   cout <<endl;

}
}
	int select_difficulty(){
		string input;
	    int number;
	
	    while (true) {
	        getline(cin, input);
	        if (input == "2" || input == "1") {
	            number = stoi(input);
	            break;
	        } else {
	            blink("Invalid input, please try again!",400);
	        }
	    }
	    cout << "You have chosen " << number <<" as your difficulty. Wish you Luck:)"<<endl;
	    return number;
	}
	bool out_range(int r, int c, vector<string> maze){
		if (r<0 || r >= maze.size() || c<0 || c>=maze[r].length()) return true; //the maze is surrounded by solid walls except the exit. if the palyer goes out of the range of the maze, he/she wins
		return false;
	}


int init_maze() {
    system("clear"); //clear the screen for better experience
    cout << GREEN << "Use WASD to control X. " << RESET << RED << "Please maximize your console for better experience. " << RESET << GREEN << "Press any key to continue" << RESET << endl << endl;
    cout << CYAN << "Please select difficulty. 1 for medium and 2 for hard. 1 or 2?" << RESET << endl;
    difficulty = select_difficulty();
    this_thread::sleep_for(chrono::milliseconds(1000));
    system("clear");
    generate_maze(difficulty);
    srand((unsigned)time(NULL));
    auto start_time = chrono::high_resolution_clock::now();
    while (true) {
        row = rand() % (maze.size() / 2); //randomly generate palyer's position. the player will not be generated in the bottom of the maze because that makes the game too easy.(the exit is located at the bottom-right corner
        col = rand() % (maze[0].size() / 2);
        if (maze[row][col] != '#' && row != 1) {
            break;
        }
    }
    maze[row][col] = 'X';
    update_status();
    printMaze_first_time();
    char c;
    system("stty -icanon"); // close buffer area to input even though the player hasn't pressed enter, which enhances experience
    while (true) {
    	auto current_time = chrono::high_resolution_clock::now();
    	auto elapsed_time = chrono::duration_cast<chrono::seconds>(current_time - start_time).count();
    	if (elapsed_time > max_time) {
            cout << "You have been traped in the maze for too long:( . The rescue team teleported from Earth will save you out." << endl;
            goto lose;
        }
        c = getchar(); //read player's movement(WASD)
        switch (c) {
            case 'w':
                if (out_range(row - 1, col, maze)) {
                    goto win;
                }
                if (!out_range(row, col, maze) && maze[row - 1][col] != '#') {
                    maze[row][col] = ' ';
                    row--;
                    maze[row][col] = 'X';
                }
                break;
            case 'a':
                if (out_range(row, col - 1, maze)) {
                    goto win;
                }
                if (maze[row][col - 1] != '#') {
                    maze[row][col] = ' ';
                    col--;
                    maze[row][col] = 'X';
                }
                break;
            case 's':
                if (out_range(row + 1, col, maze)) {
                    goto win;
                }
                if (maze[row + 1][col] != '#') {
                    maze[row][col] = ' ';
                    row++;
                    maze[row][col] = 'X';
                }
                break;
            case 'd':
                if (out_range(row, col + 1, maze)) {
                    goto win;
                }
                if (maze[row][col + 1] != '#') {
                    maze[row][col] = ' ';
                    col++;
                    maze[row][col] = 'X';
                }
                break;
            default:
                blink("Invalid input, please try again!", 400); //if the input is not WASD, the program will let the player re-enter
                break;
        }
        system("clear");
        update_status();
        printMaze();
    }
    if (row > maze.size() - 1 || col > maze[0].size() - 1) {
    win:
        cout << endl;
        cout << YELLOW << "You managed to solve the maze!" << RESET << endl;
        cout << RED << "You are a true warrior! Just take a rest now. Press any key when you are ready :)" << RESET << endl;
        pause();
        system("stty icanon"); // reenable buffer area to prevent unpredictable errors in the following program
        return 1; //return result to the main game program to indicate whether the player has guessed out the word. Here 1 indicates winning
    }
    lose:
    system("stty icanon");//re-enable buffer area to avoid unintended problem 
    return 0;//0 stands for losing
}
};
int playMaze() { //to simplify main game code, I created object "mazeGame" here
MazeGame mazeGame;
return mazeGame.init_maze();

}
