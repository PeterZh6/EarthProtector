//.cpp for displaying chapter 7 story

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
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

int ch7(){
    system("clear"); //clear the terminal
    int status;
    ifstream fin;
    ofstream fout;
    string line;
    fin.open("ch7.txt"); //Displaying chapter seven's story
    if (fin.fail()){
        cout<<RED<<"Chapter 7 cannot be displayed due to unknown issues, please try again!"<<RESET;
        cout<<"\nRedirecting to terminal...";
        sleep(1);
        exit(0);
    }
    else{
        while (getline(fin, line)){ //Read line by line, as well as detecting keywords to start game
            if (line=="Game starts!"){ //If detected keywords, start the corresponding game
                bool tmp1=true;
                bool tmp2=true;
                int count=0;
                string get;
                cout<<GREEN<<"You are entering the end story, do you wanna continue?\n";
                cout<<"Please input yes to continue: "<<RESET;
                cin>>get;
                while (tmp1==true){
                    if (get=="yes"){
                        tmp1=false;
                    }
                    else{
                        cout<<GREEN<<"Invalid input, please input again: "<<RESET;
                        cin>>get;
                    }
                }
                cout<<BLUE<<"Entering...\n"<<RESET;
                sleep(1);
                system("clear");
                string shoot;
                while (tmp2==true){
                    if (count==0){
                        //story
                        cout<<GREEN<<"Russian roulette starts!\n"<<RESET;
                        sleep(1);
                        cout<<BLUE<<"\nRules is very simple\n"
                        "there is one bullet in your and the opponent's gun\n"
                        "You two take turn to pull the trigger to shoot yourself\n"
                        "The one that lived will be the winner!\n"<<RESET;
                        sleep(1);
                        cout<<BLUE<<"\nPress Enter to continue"<<RESET;
                        cin.get();
                        cin.get();
                        cout<<"\n-------------------------------------------";
                        cout<<"\nYorgos: Vaso, I will start first!";
                        sleep(1);
                        cout<<"\nThe commander pull down the trigger, but nothing happens";
                        sleep(1);
                        cout<<"\n-------------------------------------------\n";
                        sleep(1);
                        cout<<BLUE<<"\nPlease input shoot to make your shoot: "<<RESET;
                        bool tmp3=true;
                        cin>>shoot;
                        while (tmp3==true){
                            if (shoot=="shoot"){
                                cout<<"\n-------------------------------------------\n";
                                cout<<"You pull down the trigger\n";
                                sleep(1);
                                cout<<"Nothing happens, too\n";
                                sleep(1);
                                cout<<"You then take a deep breath, and then Its the commander's turn\n";
                                cout<<"-------------------------------------------\n";
                                sleep(1);
                                tmp3=false;
                            }
                            else{
                                cout<<GREEN<<"Invalid input, please input again: "<<RESET;
                                cin>>shoot;
                            }
                        }
                        tmp2=true;
                    }
                    if (count==1){
                        //story
                        cout<<"\n-------------------------------------------";
                        cout<<"\nYorgos: Vaso, don't you wonder why I lie to you?";
                        sleep(1);
                        cout<<"\nYorgos speaks to me, while laughing";
                        sleep(1);
                        cout<<"\nHe again pulls down the trigger, but nothing happens";
                        sleep(1);
                        cout<<"\nOnly with his face laughing creepyly";
                        sleep(1);
                        cout<<"\n-------------------------------------------\n";
                        sleep(1);
                        cout<<BLUE<<"\nPlease input shoot to make your shoot: "<<RESET;
                        bool tmp3=true;
                        cin>>shoot;
                        while (tmp3==true){
                            if (shoot=="shoot"){
                                cout<<"\n-------------------------------------------\n";
                                cout<<"You, again, point the trigger to your head\n";
                                sleep(1);
                                cout<<"Then you pull down the trigger\n";
                                sleep(1);
                                cout<<"Nothing happens\n";
                                sleep(1);
                                cout<<"You then take a deep breath, and then Its the commander's turn\n";
                                cout<<"-------------------------------------------\n";
                                sleep(1);
                                tmp3=false;
                            }
                            else{
                                cout<<GREEN<<"Invalid input, please input again: "<<RESET;
                                cin>>shoot;
                            }
                        }
                        tmp2=true;
                    }
                    if (count==2){
                        cout<<"\n-------------------------------------------";
                        cout<<"\nYorgos: It seems like we two are both very lucky!";
                        sleep(1);
                        cout<<"\nYorgos adds another bullet to his gun";
                        sleep(1);
                        cout<<"\nHe again pulls down the trigger, but nothing happens";
                        sleep(1);
                        cout<<"\nNothing happens";
                        sleep(1);
                        cout<<"\n-------------------------------------------\n";
                        sleep(1);
                        cout<<BLUE<<"\nPlease input shoot to make your shoot: "<<RESET;
                        bool tmp3=true;
                        cin>>shoot;
                        while (tmp3==true){
                            if (shoot=="shoot"){
                                cout<<"\n-------------------------------------------\n";
                                cout<<"You, again, point the trigger to your head\n";
                                sleep(1);
                                cout<<"Right before you decide to pull the trigger\n";
                                sleep(1);
                                cout<<"You add all the bullets into your hand gun\n";
                                sleep(1);
                                cout<<"You then take a deep breath, and then points the gun to Yorgos\n";
                                sleep(1);
                                cout<<"And you shoot, bullet boom out, right into Yorgos's chest\n";
                                cout<<"-------------------------------------------\n";
                                sleep(1);
                                tmp3=false;
                            }
                            else{
                                cout<<GREEN<<"Invalid input, please input again: "<<RESET;
                                cin>>shoot;
                            }
                        }
                        tmp2=false;
                    }
                    count+=1;
                }
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
    cout<<BLUE<<"\nYou have finished Chapter 7, This is the end of our story, thanks for playing!\n"
          "Input q for save and quit\n"<<RESET;
    cout<<GREEN<<"Please input: "<<RESET;
    cin>>finish;
    bool help=true;
    while (help==true){
        if (finish=="q"){
            help=false;
            status=7; //Game status, number means which chapter
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
                cout<<BLUE<<"\nQuit Success!\n"<<RESET;
                cout<<BLUE<<"YOU HAVE CLEAR THE GAME! redirecting to terminal...\n"<<RESET;
                cout<<'\n';
                cout<<MAGENTA<<
"     ______           __  __       ____             __            __\n"            
"   / ____/___ ______/ /_/ /_     / __ \\_________  / /____  _____/ /_____  _____\n"
"  / __/ / __ `/ ___/ __/ __ \\   / /_/ / ___/ __ \\/ __/ _ \\/ ___/ __/ __ \\/ ___/\n"
" / /___/ /_/ / /  / /_/ / / /  / ____/ /  / /_/ / /_/  __/ /__/ /_/ /_/ / / \n"   
"/_____/\\__,_/_/   \\__/_/ /_/  /_/   /_/   \\____/\\__/\\___\\___/\\__/\\____/_/\n"<<RESET;
                cout<<'\n';
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