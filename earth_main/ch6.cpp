//.cpp for displaying chapter 6 story

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include "brainstorm.h"
#include "ch6.h" //Header file for chapter six
#include "ch7.h" //Header file for chapter seven
//The followings are color setting
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
using namespace std;

int ch6(){
    system("clear"); //clear the terminal
    int status;
    ifstream fin;
    ofstream fout;
    string line;
    fin.open("ch6.txt"); //Displaying chapter six's story
    if (fin.fail()){
        cout<<RED<<"Chapter 6 cannot be displayed due to unknown issues, please try again!"<<RESET;
        cout<<"\nRedirecting to terminal...";
        sleep(1);
        exit(0);
    }
    else{
        while (getline(fin, line)){ //Read line by line, as well as detecting keywords to start game
            if (line=="Game starts!"){ //If detected keywords, start the corresponding game
                int pass=2, skip=0;
                while (pass!=1){
                    if (pass==0){
                        cout<<GREEN<<"\nYOU LOSE, LETS TRY IT ONE MORE TIME.\nRestarting game...\n"<<RESET;
                        sleep(3);
                    }
                    pass=playBrainstorm();
                    skip+=1;
                    if (skip%2==0 and pass!=1){
                        cout<<GREEN<<"\nYou have fail this game for several times, do you wanna skip? Type yes or no: "<<RESET;
                        bool god=false;
                        string godhand;
                        cin>>godhand;
                        while (god!=true){
                            if (godhand=="yes"){
                                cout<<GREEN<<"\nSkipping game succuessful.\n"<<RESET;
                                sleep(1);
                                god=true;
                                pass=1;
                            }
                            if (godhand=="no"){
                                cout<<"Continuing the game...\n";
                                god=true;
                                pass=0;
                            }
                            if (godhand!="yes" and godhand!="no"){
                                cout<<GREEN<<"\nInvalid input, please input again: "<<RESET;
                                cin>>godhand;
                            }
                        }
                    }
                }
                cout<<BLUE<<"Press Enter to continue\n"<<RESET;
            }
            else if (line=="Loading…"){
                system("clear");
                cout<<GREEN<<"Loading...\n";
                cin.get();
                system("clear");
                cout<<"Press Enter to turn Automatic displayer on.\n";
                cin.get();
                system("clear");
                cout<<"Heading toward the next planet...\n";
                sleep(1);
                system("clear"); //Automatic display of spaceship from origin to destination
                cout<<"      ------------------------------\n"
                      "From |>                             | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |  >                           | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |    >                         | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |      >                       | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |        >                     | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |           >                  | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |              >               | To\n"
                      "      ------------------------------\n";
                sleep(1);
                system("clear");
                cout<<"      ------------------------------\n"
                      "From |              >"<<RED<<"!"<<RESET<<GREEN<<"              | To\n"
                      "      ------------------------------\n"<<RESET;
                sleep(1);
                cout<<RED<<"Please Press Enter to continue.\n"<<RESET;     
                
            }
            else{
                cout<<line;
            }
            cin.get();
        }
    }
    fin.close();
    string finish; //End of the chapter, giving player to choice continue or quit, both will gave game status
    cout<<BLUE<<"\nYou have finished Chapter 6, do you want to continue or save and quit?\n"
          "Input c for continue, and q for save and quit\n"<<RESET;
    cout<<GREEN<<"Please input: "<<RESET;
    cin>>finish;
    bool help=true;
    while (help==true){
        if (finish=="c"){
            status=6; //Game status, number means which chapter
            fout.open("status.txt");
            if (fout.fail()){
                cout<<RED<<"Unknown errors occur, redirecting to terminal"<<RESET;
                exit(0);
            }
            else{
                fout<<status;
            }
            fout.close();
            ch7(); //The Next Chapter Starts Here
            help=false;
        }
        else if (finish=="q"){
            help=false;
            status=6; //Game status, number means which chapter
            fout.open("status.txt");
            if (fout.fail()){
                cout<<RED<<"Unknown errors occur, redirecting to terminal"<<RESET;
                exit(0);
            }
            else{
                fout<<status;
            }
            fout.close();
            fin.open("status.txt"); //Display the saved status to player
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
            fin.close();
        }
        else{
            cout<<GREEN<<"Invalid input, please input again: "<<RESET;
            cin>>finish;
        }
    }
    return 0;
}
