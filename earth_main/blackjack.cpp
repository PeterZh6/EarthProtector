// blackjack.cpp

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <thread>
#include <random>
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#include "blackjack.h"
using namespace std;

// Card struct
struct Card {
    string suit;
    string rank;
    int value;
};

// Function to pause the program until press Enter
static void pause() { 
    cin.get();
}

// Function to pause the program for a while
static void sleep(int sleep_time = 2000) {
    this_thread::sleep_for(chrono::milliseconds(sleep_time));
}

// Function to deal with invalid input
static void issueWarning() {
    cout << BOLD << RED << "\nInvalid input. Pls input again!" << RESET << endl;
}

// Function to print a hand of cards
void printHand(vector<Card> hand) {
    vector<Card>::iterator itr;
    for (itr = hand.begin(); itr != hand.end(); itr++) {
        cout << itr->rank << " of " << itr->suit << endl;
    }
}

// Function to get the total value of a hand
int getTotalValue(vector<Card> hand) {
    int totalValue = 0;
    int numAces = 0;
    vector<Card>::iterator itr;
    for (itr = hand.begin(); itr != hand.end(); itr++) {
        totalValue += itr->value;
        if (itr->rank == "Ace") {
            numAces++;
        }
    }
    while (totalValue > 21 && numAces > 0) {  // Ace is couted as either 1 or 11 for the best of the player
        totalValue -= 10;
        numAces--;
    }
    return totalValue;
}

// Function to create a deck of cards
vector<Card> createDeck() {
    vector<Card> deck;
    string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
    string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    int values[] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    int index = 0;
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 4; j++) {
            Card card;
            card.rank = ranks[i];
            card.suit = suits[j];
            card.value = values[i];
            deck.push_back(card);
        }
    }
    // shuffle the deck of cards
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), default_random_engine(seed));
    return deck;
}

// Function to print game status
void printStatus(double previous_status, double current_status, double target_status) {
    cout << "\nYour net gain in this round of blackjack is: " << BOLD << RED << current_status - previous_status << RESET << endl;
    cout << "Currently, you have " << BOLD << RED << current_status << RESET << " dollars" << endl;
    if (target_status - current_status > 0) {
        cout << "You still need to win " << RED << BOLD << target_status - current_status << RESET << " to resume the journey" << endl;
    }
}

// Function to play game for a single round
bool runGame(double &current_status, double target_status) {
    double previous_status = current_status;
    double bet;
    vector<Card> deck = createDeck();
    vector<Card> playerHand;
    vector<Card> robotHand;
    sleep(1000);
    cout << "\nHow much do you want to bet this time? (Only integer amount is allowed)" << endl;
    cin >> bet;
    while (bet > current_status) {
        cout << BOLD << RED << "\nYou don't have enough money. Pls input again." << RESET << endl;
        cin >> bet;
    }
    // deal the initial two cards
    playerHand.push_back(deck.back());
    deck.pop_back();
    robotHand.push_back(deck.back());
    deck.pop_back();
    playerHand.push_back(deck.back());
    deck.pop_back();
    robotHand.push_back(deck.back());
    deck.pop_back();
    sleep(1000);
    cout << BOLD << BLUE << "\nInitial Hand" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    cin.ignore();
    pause();
    cout << "Your Hand:" << endl;
    printHand(playerHand);
    cout << "Your Total: " << UNDERLINE << getTotalValue(playerHand) << RESET << endl;
    pause();
    cout << "Robot's Hand:" << endl;
    printHand(robotHand);
    cout << "Robot's Total: " << UNDERLINE << getTotalValue(robotHand) << RESET << endl;
    // check for blackjack
    if (getTotalValue(playerHand) == 21 || getTotalValue(robotHand) == 21) {
        if (getTotalValue(robotHand) != 21) {
            sleep();
            cout << "\nRobot: OhNooooooo, why you're so lucky." << endl;
            cout << BOLD << RED << "You get Blackjack! You win!" << RESET << endl;
            current_status += 1.5*bet; // blackjack pays 3 to 2
            sleep();
            printStatus(previous_status, current_status, target_status);
            if (current_status >= target_status || current_status <= 0) {
                return 1;
            } 
            else {
                return 0;
            }
        }
        else if (getTotalValue(playerHand) != 21) {
            sleep();
            cout << "\nRobot: Luck is also part of my strength." << endl;
            cout << BOLD << RED << "Robot gets Blackjack! You lose!" << RESET << endl;
            current_status -= bet;
            sleep();
            printStatus(previous_status, current_status, target_status);
            if (current_status >= target_status || current_status <= 0) {
                return 1;
            } 
            else {
                return 0;
            }
        }
        else {
            sleep();
            cout << "\nRobot: What a coincidence!" << endl;
            cout << BOLD << RED << "Both Blackjack! Push!" << RESET << endl;
            sleep();
            printStatus(previous_status, current_status, target_status);
            if (current_status >= target_status || current_status <= 0) {
                return 1;
            } 
            else {
                return 0;
            }
        }
    }
    else {
        // player decision making
        pause();
        cout << "Do you want to double down OR surrender OR not? (Pls input d/s/n accordingly)" << endl;
        char player_option;
        while (cin >> player_option) {
            if (player_option == 'd') {
                if (current_status >= 2*bet) {
                    cout << BOLD << RED << "\nAccepted!" << RESET << endl;
                    cout << "(Press Enter to continue)" << endl;
                    bet *= 2;
                }
                else {
                    cout << BOLD << RED << "\nYou don't have enough money." << RESET << endl;
                    cout << "(Press Enter to continue)" << endl;
                }
                break;
            } 
            else if (player_option == 's') {
                cout << BOLD << RED << "\nAccepted!" << RESET << endl;
                current_status -= 0.5*bet;
                sleep();
                printStatus(previous_status, current_status, target_status);
                if (current_status >= target_status || current_status <= 0) {
                    return 1;
                } 
                else {
                    return 0;
                }
            } 
            else if (player_option == 'n') {
                cout << BOLD << RED << "\nAccepted" << RESET << endl;
                cout << "(Press Enter to continue)" << endl;
                break;
            } 
            else {
                issueWarning();
            }
        }
    }
    // decide who goes first
    char player_option, robot_option;
    bool player_over = false, robot_over = false;
    cin.ignore();
    pause();
    cout << "Robot: To be fair, let's flip a coin to decide who goes first.";
    pause();
    cout << "If it is a head then you go first; otherwise I make the first move.";
    pause();
    cout << "(Press Enter to flip a coin)" << endl;
    pause();
    char coin_flip = (rand() % 2 == 1)? 'h':'t';
    if (coin_flip == 'h') {
        cout << BOLD << RED << "The coin shows a head. It's your turn now." << RESET << endl;
        while (true) {
            if (!player_over) {
                // player's turn
                sleep(1000);
                cout << BOLD << BLUE << "\nYour Turn" << RESET << endl;
                cout << "\nDo you want to hit or stand? \nPls input h/s for hit/stand respectively." << endl;
                while (cin >> player_option) {
                    if (player_option == 'h') {
                        playerHand.push_back(deck.back());
                        deck.pop_back();
                        cout << "\nAfter you draw one more card..." << endl;
                        sleep();
                        cout << "\nYour Hand:" << endl;
                        printHand(playerHand);
                        cout << "Your Total: " << UNDERLINE << getTotalValue(playerHand) << RESET << endl;
                        // check if player busted
                        if (getTotalValue(playerHand) > 21) {
                            sleep();
                            cout << "\nRobot: HaHa. Greed is enemy." << endl;
                            cout << BOLD << RED << "Busted! You lose!" << RESET << endl;
                            current_status = current_status - bet;
                            sleep();
                            printStatus(previous_status, current_status, target_status);
                            if (current_status >= target_status || current_status <= 0) {
                                return 1;
                            } 
                            else {
                                return 0;
                            }
                        }
                        break;
                    }
                    else if (player_option == 's') {
                        player_over = true;
                        cout << "\nYour turn is over!" << endl;
                        break;
                    }
                    else {
                        issueWarning();
                    }
                }
            }
            if (!robot_over) {
                // robot's turn
                sleep(1000);
                cout << BOLD << BLUE << "\nRobot's Turn" << RESET << endl;
                if (getTotalValue(robotHand) >= getTotalValue(playerHand)) {
                    if (player_over) {
                        robot_option = 's';
                    }
                    else {
                        if (getTotalValue(robotHand) < 11) {
                            robot_option = 'h';
                        }
                        else if (getTotalValue(robotHand) > 17) {
                            robot_option = 's';
                        }
                        else {
                            if (getTotalValue(robotHand) > getTotalValue(playerHand)+8) {
                                robot_option = (rand() % 10 < 4)? 'h':'s';
                            }
                            else {
                                robot_option = (rand() % 10 < 8)? 'h':'s';
                            }
                        }
                    }
                }
                else {
                    robot_option = 'h';
                }
                if (robot_option == 'h') {
                    sleep(3000);
                    cout << "\nThe Robot decides to draw card. \nRobot: God, pls give me the best hand!" << endl;
                    robotHand.push_back(deck.back());
                    deck.pop_back();
                    sleep();
                    cout << "\nAfter Robot draws one more card..." << endl;
                    sleep();
                    cout << "\nRobot's Hand:" << endl;
                    printHand(robotHand);
                    cout << "Robot's Total: " << UNDERLINE << getTotalValue(robotHand) << RESET << endl;
                    // check if robot busted
                    if (getTotalValue(robotHand) > 21) {
                        sleep();
                        cout << "\nRobot: OhNoooooo, I bust." << endl;
                        cout << BOLD << RED << "Robot Busted! You win!" << RESET << endl;
                        current_status = current_status + bet;
                        sleep();
                        printStatus(previous_status, current_status, target_status);
                        if (current_status >= target_status || current_status <= 0) {
                            return 1;
                        } 
                        else {
                            return 0;
                        }
                    }
                }
                else {
                    robot_over = true;
                    sleep(3000);
                    cout << "\nThe Robot decides to stop drawing card, and Robot's turn is over! \nRobot: Just wait and see" << endl;
                }
            }
            if (player_over && robot_over) {
                sleep();
                cout << "\nAs both you and robot stop drawing cards, the game ends." << endl;
                sleep(1000);
                cout << BOLD << BLUE << "\nFinal Hand" << RESET << endl;
                cout << "(Press Enter to continue)" << endl;
                cin.ignore();
                pause();
                cout << "Your Hand:" << endl;
                printHand(playerHand);
                cout << "Your Total: " << UNDERLINE << getTotalValue(playerHand) << RESET << endl;
                pause();
                cout << "Robot's Hand:" << endl;
                printHand(robotHand);
                cout << "Robot's Total: " << UNDERLINE << getTotalValue(robotHand) << RESET << endl;
                if (getTotalValue(playerHand) > getTotalValue(robotHand)) {
                    sleep();
                    cout << "\nRobot: I just made a mistake. Let's wait and see." << endl;
                    cout << BOLD << RED << "You win!" << endl;
                    current_status = current_status + bet;
                    sleep();
                    printStatus(previous_status, current_status, target_status);
                    if (current_status >= target_status || current_status <= 0) {
                        return 1;
                    } 
                    else {
                        return 0;
                    }
                }
                else if (getTotalValue(playerHand) < getTotalValue(robotHand)) {
                    sleep();
                    cout << "\nRobot: Young man you need to practice more HAHAHAHAHAHA..." << endl;
                    cout << BOLD << RED << "You lose!" << RESET << endl;
                    current_status = current_status - bet;
                    sleep();
                    printStatus(previous_status, current_status, target_status);
                    if (current_status >= target_status || current_status <= 0) {
                        return 1;
                    } 
                    else {
                        return 0;
                    }
                }
                else {
                    sleep();
                    cout << "\nRobot: Wow, I didn't expect it to be a draw." << endl;
                    cout << BOLD << RED << "Push!" << RESET << endl;
                    current_status = current_status;
                    sleep();
                    printStatus(previous_status, current_status, target_status);
                    if (current_status >= target_status || current_status <= 0) {
                        return 1;
                    } 
                    else {
                        return 0;
                    }
                }
            }
        }
    }
    else {
        cout << BOLD << RED << "The coin shows a tail. The robot will go first." << RESET << endl;
        while (true) {
            if (!robot_over) {
                // robot's turn
                sleep(1000);
                cout << BOLD << BLUE << "\nRobot's Turn" << RESET << endl;
                if (getTotalValue(robotHand) >= getTotalValue(playerHand)) {
                    if (player_over) {
                        robot_option = 's';
                    }
                    else {
                        if (getTotalValue(robotHand) < 11) {
                            robot_option = 'h';
                        }
                        else if (getTotalValue(robotHand) > 17) {
                            robot_option = 's';
                        }
                        else {
                            if (getTotalValue(robotHand) > getTotalValue(playerHand)+8) {
                                robot_option = (rand() % 10 < 4)? 'h':'s';
                            }
                            else {
                                robot_option = (rand() % 10 < 8)? 'h':'s';
                            }
                        }
                    }
                }
                else {
                    robot_option = 'h';
                }
                if (robot_option == 'h') {
                    sleep(3000);
                    cout << "\nThe Robot decides to draw card. \nRobot: God, pls give me the best hand!" << endl;
                    robotHand.push_back(deck.back());
                    deck.pop_back();
                    sleep();
                    cout << "\nAfter Robot draws one more card..." << endl;
                    sleep();
                    cout << "\nRobot's Hand:" << endl;
                    printHand(robotHand);
                    cout << "Robot's Total: " << UNDERLINE << getTotalValue(robotHand) << RESET << endl;
                    // check if robot busted
                    if (getTotalValue(robotHand) > 21) {
                        sleep();
                        cout << "\nRobot: OhNoooooo, I bust." << endl;
                        cout << BOLD << RED << "Robot Busted! You win!" << RESET << endl;
                        current_status = current_status + bet;
                        sleep();
                        printStatus(previous_status, current_status, target_status);
                        if (current_status >= target_status || current_status <= 0) {
                            return 1;
                        } 
                        else {
                            return 0;
                        }
                    }
                }
                else {
                    robot_over = true;
                    sleep(3000);
                    cout << "\nThe Robot decides to stop drawing card. \nRobot's turn is over!" << endl;
                }
            }
            if (!player_over) {
                // player's turn
                sleep(1000);
                cout << BOLD << BLUE << "\nYour Turn" << RESET << endl;
                cout << "\nDo you want to hit or stand? \nPls input h/s for hit/stand respectively." << endl;
                while (cin >> player_option) {
                    if (player_option == 'h') {
                        playerHand.push_back(deck.back());
                        deck.pop_back();
                        cout << "\nAfter you draw one more card..." << endl;
                        sleep();
                        cout << "\nYour Hand:" << endl;
                        printHand(playerHand);
                        cout << "Your Total: " << UNDERLINE << getTotalValue(playerHand) << RESET << endl;
                        // check if player busted
                        if (getTotalValue(playerHand) > 21) {
                            sleep();
                            cout << "\nRobot: HaHa. Greed is enemy." << endl;
                            cout << BOLD << RED << "Busted! You lose!" << RESET << endl;
                            current_status = current_status - bet;
                            sleep();
                            printStatus(previous_status, current_status, target_status);
                            if (current_status >= target_status || current_status <= 0) {
                                return 1;
                            } 
                            else {
                                return 0;
                            }
                        }
                        break;
                    }
                    else if (player_option == 's') {
                        player_over = true;
                        cout << "\nYour turn is over!" << endl;
                        break;
                    }
                    else {
                        issueWarning();
                    }
                }
            }
            if (player_over && robot_over) {
                sleep();
                cout << "\nAs both you and robot stop drawing cards, the game ends." << endl;
                sleep(1000);
                cout << BOLD << BLUE << "\nFinal Hand" << RESET << endl;
                cout << "(Press Enter to continue)" << endl;
                cin.ignore();
                pause();
                cout << "Your Hand:" << endl;
                printHand(playerHand);
                cout << "Your Total: " << UNDERLINE << getTotalValue(playerHand) << RESET << endl;
                pause();
                cout << "Robot's Hand:" << endl;
                printHand(robotHand);
                cout << "Robot's Total: " << UNDERLINE << getTotalValue(robotHand) << RESET << endl;
                if (getTotalValue(playerHand) > getTotalValue(robotHand)) {
                    sleep();
                    cout << "\nRobot: I just made a mistake. Let's wait and see." << endl;
                    cout << BOLD << RED << "You win!" << RESET << endl;
                    current_status = current_status + bet;
                    sleep();
                    printStatus(previous_status, current_status, target_status);
                    if (current_status >= target_status || current_status <= 0) {
                        return 1;
                    } 
                    else {
                        return 0;
                    }
                }
                else if (getTotalValue(playerHand) < getTotalValue(robotHand)) {
                    sleep();
                    cout << "\nRobot: Young man you need to practice more HAHAHAHAHAHA..." << endl;
                    cout << BOLD << RED << "You lose!" << RESET << endl;
                    current_status = current_status - bet;
                    sleep();
                    printStatus(previous_status, current_status, target_status);
                    if (current_status >= target_status || current_status <= 0) {
                        return 1;
                    } 
                    else {
                        return 0;
                    }
                }
                else {
                    sleep();
                    cout << "\nRobot: Wow, I didn't expect it to be a draw." << endl;
                    cout << BOLD << RED << "Push!" << RESET << endl;
                    current_status = current_status;
                    sleep();
                    printStatus(previous_status, current_status, target_status);
                    if (current_status >= target_status || current_status <= 0) {
                        return 1;
                    } 
                    else {
                        return 0;
                    }
                }
            }
        }
    }
}

bool playBlackjack() {
    bool game_over = false;
    double current_status = 10000;
    double target_status = 50000;
    sleep(1000);
    cout << BOLD << BLUE << "\nGame Rule" << RESET << endl;
    cout << "(Press Enter to continue)" << endl;
    pause();
    cout << "1. You have to win extra " << BOLD << "$40,000 " << RESET << "with your own " << BOLD << "$10,000" << RESET << ".";
    pause();
    cout << "You can only bet for an integer amount of money each time.";
    pause();
    cout << "2. To win the game, you need to get as close to 21 as possible, but not exceeding 21.";
    pause();
    cout << "Anyone with total value beyond 21 will lose immediately.";
    pause();
    cout << "3. You and your opponent will take turns to draw cards, until both of you choose to stand.";
    pause();
    cout << "You will not be allowed to draw card anymore once you choose to stand.";
    pause();
    cout << "The game ends when both players choose to stand, and the one with higher total value (below 21) wins.";
    pause();
    cout << "4. Following are a few options available for the player:";
    pause();
    cout << "- " << BOLD << "Hit: " << RESET << "draw one more card";
    pause();
    cout << "- " << BOLD << "Stand: " << RESET << "stop drawing card";
    pause();
    cout << "- " << BOLD << "Double down: " << RESET << "double your bet";
    pause();
    cout << "- " << BOLD << "Surrender: " << RESET << "give up current round but lose only 1/2 of your bet" << endl;
    while (!game_over) {
        game_over = runGame(current_status, target_status);
    }
    sleep();
    if (current_status > 0) {
        cout << BOLD << RED << "\nCongratulations! You have made enough money." << RESET << endl;
        return 1;
    } 
    else {
        cout << BOLD << RED << "\nYou have lost all your money. Mission failed!"  << RESET << endl;
        return 0;
    }
}
