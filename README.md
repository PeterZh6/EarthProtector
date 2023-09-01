# EARTHPROTECTOR 
## ENGG1340/COMP2113 Group Project (Group 151)

Welcome to EarthProtector!  
This repo is for group project of HKU course ENGG1340/COMP2113 2BC 2022.

## Author Information

This game is developed by the following four authors (sorted alphabetically by surname): 
| Name | UID | Account |
| ------------- | ------------- | ----------------- |
| Chai Ming How  | 3036086476  | ChaiMingHow |
| Sun Shengyao  | 3036051500 | fd2374 |
| Yao Zixuan | 3035845148 | zxyao5148 |
| Zhang Hengyuan | 3036051586 | PeterZh6 |

## About Contribution

Please note that the contribution graph shown on github does not represent the actual workload distribution for two reasons:

* We have a whole dictionary for one of our mini game (wordle) within the main game, and this txt file has explosive huge amount of lines count which affects the contribution graph.
* We usually work in offline meetings and having one person to upload all the codes onto github, which affects the contribution ratio as well.

***Declaration: Here we declare that there is no problem for the division of labour within our group. The workload is evenly distributed among all four group members!***

## User Guide
* Please open the terminal as the maximum size to have better game experience.
* Plese make sure that your current directory is called __"earth_main"__ with all the downloaded files within this directory.  
* You may use shell command `ls` to see if all files are already available in the current directory.  
* Then, type command `make earthprotector` into the terminal. This will automatically complie the game program.  
* Last, type command `./earthprotector` into the terminal, and you are ready to play!  
* You may also use the command `make clean` to clean the directory (including all .o files and earthprotector) as well.  
* We have incorporated skip game function in our game. If you fail too many times for a mini game, you will be given an option to skip that game.  

The above steps are also demonstrated in our [3-min video](https://connecthkuhk-my.sharepoint.com/:f:/g/personal/u3608647_connect_hku_hk/EvGQ_BHIJ-pGsXmIpsEqdpUBgnnDtxk4bNxaThkXyXwhJw?e=1Nf8iQ), feel free to check it if needed. You are welcomed to contact us if you have further questions.

## Game Overview

2089-02-14

There is an alien invasion on Earth.  
You, our hero, named Vaso,  
under the command of your commander named Yorgos,  
take on a journey to defeat the aliens' home planets!  
However, things seem a little suspectable...  

In our game, you are going to visit multiple planets, each has a mini game and wonderful storyline within!  
We have many genres of mini games with the whole story, as well as a smooth and dramatic storyline.  
Summary of each mini game is provided as follows while more details could be found under the Game Rules section.  
In the fighting and blackjack game you are going to play against the computer-player (with random strategy),   
while other games listed below are all single-player game.

1. __Music game__: use 1234 on keyboard to hit the targets that fall to the buttom, better the timing higher the score

2. __Wordle__: guess out the word in six attempts

3. __Maze__: escape the maze within 2 minutes

4. __Fight__: use attack and skill to defeat your oppoent

5. __Blackjack__: play a modified version of blackjack game 

6. __Brainstrom__: answer a few tricky (e.g., wordplay) questions

7. __Russian roulette__: play a standard russian roulette game  

## Special Features

We have implemented a range of special features in our game. Here are the explainations on how those features are achieved by the coding elements required.

1. __Generation of random game sets or events__:  
Our game has very high randomness, which makes the story unpredictable and dramatic. You will have different game experiences when you play the mini games for multiple times. There are many random elements in our game, such as the random card shuffling and computer strategy in blackjack, random question selected in brainstorm, random effects of attacks in fighting-game, random starting position generated in maze, etc.

2. __Data structures for storing game status__:  
Our game allows players to save and load game status at the end of each chapter. You can save and quit at the end of each chapter, and load your saved game status after you start the game program again.

3. __Dynamic memory management__:  
Our game attempts to minimize the memory usage, by utilizing dynamic memory management such as dynamic arrays across the programs, e.g., the class in the game wordle.

4. __File I/O__:  
Our game has a very rich story line and detailed instructions, which is achieved by inputting and outputting from multiple text files within the game for different purposes. We also wrote functions to formatting the text inputs, e.g., the function in the brainstorm game.

5. __Program codes in multiple files__:  
Our game has highly readable source codes, in which different functionalities are realized in separate files. As in our __"earth_main"__ directory, we have separated different mini-games into individual cpp files. This facilitates the control and manipulation of our game plays, and also makes our work more readable.

6. __Proper indentation and naming styles__:  
Although our group aims to produce a game that consists of many mini games with different game genres, we have an agreement on the general naming styles when coding our programs. The overall style in our codes is clear and clean.

7. __In-code documentation__:  
We have incorparated a wide range of in-code comments, which clearly illustrate the function of a chunk of code where necessary.

## Game Rules

### Ch1 Rock n’ Roll!!!!!
* There will be targets falling to the buttom with gradually increasing speed.
* You need to click __1 2 3 4__ on your keyboard to hit the targets.
  - better the timing higher the score you get!
  - If you miss for three times you will lose and retry the game.
* After earning score __>= 200000__, you win the game!

### Ch2 Desert…Desert…Desert…and Tresure!
* Press any key to continue.
* You have to guess the Wordle in __six__ goes or less.
* Every word you enter must be in the word list. 
* A correct letter turns green.
* A correct letter in the wrong place turns yellow.
* An incorrect letter turns gray.
* Letters can be used more than once.
* Answers are never plurals.

### Ch3 The Lost Forest
* You need to escape the maze within the time limit of __2-min__, using __WASD__ to control for the movement.
* You can choose the difficulty at the beginning.

### Ch4 What The Hell Is This Thing!?
There is no special rule for this game. Please pay attention to the pomped-out instructions when you run the program!

### Ch5 Poker Joker
* You have to win extra __$40,000__ with your own __$10,000__. You can only bet for an integer amount of money each time.
* To win the game, you need to get as close to 21 as possible, but not exceeding 21. Anyone with total value beyond 21 will lose immediately.
* You and your opponent will take turns to draw cards, until both of you choose to stand. You will not be allowed to draw card anymore once you choose to stand. The game ends when both players choose to stand, and the one with higher total value (below 21) wins.
* Following are a few options available for the player:
  - __Hit__: draw one more card
  - __Stand__: stop drawing card
  - __Double down__: double your bet
  - __Surrender__: give up current round but lose only 1/2 of your bet

### Ch6 Unknown Title
* You need to solve __four__ brain-teaser questions (randomly selected from a problem bank) to pass the game.
  - For multiple-choice questions, there will only be one chance to answer.
  - Non multiple-choices questions allow you to reponse for up to three times.
* You will be given a chance to jump a question after you answer wrongly for three times.
* You can choose either "Easy" or "Hard" mode at the beginning. You pass the game as long as you answer four questions correctly, no matter of which mode you choose.
* All user inputs in this game should be in upper case!


For more enquiries, feel free to contact Martin at +852 93727642 at Whatsapp, or email martin.chaimh@gmail.com
