//This is the main function for game story displaying and playing
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "ch0.h" //Header file for chapter zero
#include "ch1.h" //Header file for chapter one
#include "ch2.h" //Header file for chapter two
#include "ch3.h" //Header file for chapter three
#include "ch4.h" //Header file for chapter four
#include "ch5.h" //Header file for chapter five
#include "ch6.h" //Header file for chapter six
#include "ch7.h" //Header file for chapter seven
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
using namespace std;

//main function
int main(){
    ifstream fin;
    int status;
    cout<<'\n';
    //Some start-up insturction for playing
    cout << GREEN << "Welcome to EarthProtector.\n"
            "Stories are processed either automatically or by pressing enter buttons.\n"
            "Instrution will be given on the screen, as well as game rules.\n"
            "You are only able to save game after each chapter, if you quit during a chapter,\n"
            "You will need to restart at that chapter, chapter cannot be saved in the middle\n"
            "Invalid input will be detected during the game, error message will be displayed\n"
            "We Hope You have a good game experience,\n"
            "By Chai Ming How, Sun Shengyao, Yao Zixuan, Zhang Hengyuan.\n" << RESET;
    cout<<'\n';
    cout << BLUE << "Make sure you understand the above message, then press enter to continue" << RESET;
    cin.get(); //press enter to continue the code
    system("clear"); //clear the contents on the terminal
    cout << MAGENTA <<
"     ______           __  __       ____             __            __\n"            
"   / ____/___ ______/ /_/ /_     / __ \\_________  / /____  _____/ /_____  _____\n"
"  / __/ / __ `/ ___/ __/ __ \\   / /_/ / ___/ __ \\/ __/ _ \\/ ___/ __/ __ \\/ ___/\n"
" / /___/ /_/ / /  / /_/ / / /  / ____/ /  / /_/ / /_/  __/ /__/ /_/ /_/ / / \n"   
"/_____/\\__,_/_/   \\__/_/ /_/  /_/   /_/   \\____/\\__/\\___\\___/\\__/\\____/_/\n" << RESET
         << BLUE << "\nPress 1 to start a new game\n"
            "Press 2 to continue previous saved game\n"
            "Press q to save and quit game\n" << RESET;
    cout << BLUE << "Please input: " << RESET;
    string input;
    cin>>input;
    bool help=true;
    while (help==true){ //while statement for detecting validity of input
        if (input=="1"){ //option one is opening a new game
            help=false;
            ifstream fin;
            fin.open("ch0.txt"); //check if chapter 0 is displaying successfully
            if (fin.fail()){
                cout<<RED<<"Chapter 0 cannot be displayed due to unknown issues, please try again!"<<RESET;
                cout<<"\nRedirecting to terminal...";
                sleep(1);
                exit(0);
            }
            else{
                ch0();
            }
        }
        if (input=="2"){ // load game status and go into the corresponding chapter for the saved game
            help=false;
            fin.open("status.txt");
            if (fin.fail()){
                cout<<RED<<"Unknown errors occur, redirecting to terminal"<<RESET;
                exit(0);
            }
            else{
                fin>>status;
                if (status==0){
                    cout<<GREEN<<"Proceeding to chapter zero"<<RESET;
                    sleep(1);
                    system("clear");
                    ch0();
                }
                if (status==1){
                    cout<<GREEN<<"You have finished Chapter 1, proceeding to Chapter 2..\n"<<RESET;
                    sleep(1);
                    system("clear");
                    ch2();
                }
                if (status==2){
                    cout<<GREEN<<"You have finished Chapter 2, proceeding to Chapter 3..\n"<<RESET;
                    sleep(1);
                    system("clear");
                    ch3();
                }
                if (status==3){
                    cout<<GREEN<<"You have finished Chapter 3, proceeding to Chapter 4..\n"<<RESET;
                    sleep(1);
                    system("clear");
                    ch4();
                }
                if (status==4){
                    cout<<GREEN<<"You have finished Chapter 4, proceeding to Chapter 5..\n"<<RESET;
                    sleep(1);
                    system("clear");
                    ch5();
                }
                if (status==5){
                    cout<<GREEN<<"You have finished Chapter 5, proceeding to Chapter 6..\n"<<RESET;
                    sleep(1);
                    system("clear");
                    ch6();
                }
                if (status==6){
                    cout<<GREEN<<"You have finished Chapter 6, proceeding to Chapter 7..\n"<<RESET;
                    sleep(1);
                    system("clear");
                    ch7();
                }
                if (status==7){
                    cout<<GREEN<<"You have finished the game already! Do you wanna start a new game?\n";
                    cout<<"Please input yes for continue a new game: "<<RESET;
                    bool tmpt=true;
                    string finalinput;
                    cin>>finalinput;
                    while (tmpt==true){
                        if (finalinput=="yes"){
                            tmpt=false;
                            cout<<BLUE<<"Proceeding to chapter zero...\n"<<RESET;
                            sleep(1);
                            system("clear");
                            ch0();
                        }
                        else{
                            cout<<GREEN<<"Invalid input, please try again: "<<RESET;
                            cin>>finalinput;
                        }
                    }
                }
                fin.close();
            }
        }
        if (input=="q"){
            help=false;
            fin.open("status.txt");
            if (fin.fail()){
                cout<<RED<<"Unknown errors occur, redirecting to terminal"<<RESET;
                exit(0);
            }
            else{
                fin>>status;
                cout<<GREEN<<"\nSAVE Success!\n";
                cout<<"Your current saving status is Chapter "<<status<<", redirecting to terminal..."<<RESET;
                exit(0);
            }
        }
        if (input!="1" and input!="2" and input!="q"){
            cout<<GREEN<<"\nInvalid input, please input again: "<<RESET;
            cin>>input;
        }
    }
    return 0;
}