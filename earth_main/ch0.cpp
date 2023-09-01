//.cpp for displaying chapter 0 story

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include "ch0.h" //Header file for chapter zero
#include "ch1.h" //Header file for chapter one
//The followings are color setting
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
using namespace std;

int ch0(){
    system("clear");
    int status;
    ifstream fin;
    ofstream fout;
    string line;
    fin.open("ch0.txt"); //Displaying chapter zero's story
    if (fin.fail()){
        cout<<RED<<"Chapter 0 cannot be displayed due to unknown issues, please try again!"<<RESET;
        cout<<"\nRedirecting to terminal...";
        sleep(1);
        exit(0);
    }
    else{
        cout<<GREEN<<"Press Enter to turn Automic displayer on.\n"<<RESET;
        cin.get();
        cin.get();
        cout<<"Loading..."<<'\n';
        sleep(1);
        cout<<"Loading successful."<<'\n';
        sleep(1);
        cout<<"Loading diary in..."<<'\n';
        sleep(1);
        cout<<"3 sec..."<<'\n';
        sleep(1);
        cout<<"2 sec..."<<'\n';
        sleep(1);
        cout<<"1 sec..."<<'\n';
        sleep(1);
        cout<<"Reading in..."<<'\n';
        sleep(1);
        system("clear");
        cout<<GREEN<<"Please press enter to continue."<<RESET;
        cin.get();
        while (getline(fin, line)){
            if (line=="---------CHAPTER 0----------"){
                system("clear");
            }
            cout<<line;
            cin.get();
        }
    }
    fin.close();
    ch1(); //Connect to the next chapter
    return 0;
}