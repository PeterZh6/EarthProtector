#include <bits/stdc++.h>
#include <termios.h>
#include <unistd.h>
#include "music_game.h"
using namespace std;
//the size of the game board
const int maxx=10,maxy=4;
//the time between two notes and lives
int wait_time=1000000,life=3;
//the gameboard class 
class Board{
	private:
		char mp[100][100];
	public:
		int point;
		Board();
		//print the whole map
		void print(bool flag)
		{
			cout << "\033[2J\033[1;1H";
			printf("Point: %d\n",point);
			for(int i=1;i<=life;i++)
			{
				printf("\u2764 ");
			}
			printf("\n");
			for(int i=1;i<maxx;i++)
			{
				for(int j=1;j<=maxy;j++)
				{
					printf("%c%c|",mp[i][j],mp[i][j]);
				}
				printf("\n");
			}
			for(int j=1;j<=maxy;j++)
			{
				if(flag&&mp[maxx][j]=='@')printf("##|");
				else printf("%c%c|",mp[maxx][j],mp[maxx][j]);
			}
			printf("\n");
			for(int j=1;j<=maxy;j++)printf("%d  ",j);
			printf("\n");
		}
		bool isright(char c)
		{
			int num=c-'0';
			return mp[maxx][num]=='@';
		}
		//refresh the status
		void refresh()
		{
			for(int i=maxx;i>=2;i--)
			{
				for (int j=1;j<=maxy;j++)
				{
					mp[i][j]=mp[i-1][j];
				}
			}
			for(int i=1;i<=maxy;i++)
			{
				mp[1][i]='.';
			}
			mp[1][rand()%maxy+1]='@';
		}
		int count()
		{
			int rest=0;
			for(int i=1;i<=maxy;i++)
			{
				if(mp[maxx][i]=='@')rest++;
			}
			return rest;
		}
}B;
//initialize the map
Board::Board()
{
	srand(time(NULL));
	for(int i=1;i<=maxx;i++)
	{
		for(int j=1;j<=maxy;j++)
		{
			mp[i][j]='.';
		}
	}
	point=0;
}
//got the input without entering linebreaker
char getch(int wait_time) {
	struct timeval timeout;
	timeout.tv_sec = 0;
	timeout.tv_usec = wait_time;
	fd_set readfds;
	FD_ZERO(&readfds);
	FD_SET(STDIN_FILENO, &readfds);
	char ch;
        int ret = select(STDIN_FILENO + 1, &readfds, NULL, NULL, &timeout);
        if (ret == 0) 
        {
        	return '0';
        } 
        else 
        {
        	cin>>ch;
                return ch;
        }
}
//get the running time (millisecond)
int get_time()
{
	struct timespec T;
	clock_gettime(CLOCK_MONOTONIC, &T);
	long seconds = T.tv_sec;
	long nanoseconds = T.tv_nsec;
	int elapsed_time = seconds*1000 + nanoseconds*1e-6;
	return elapsed_time;
}
struct termios oldt, newt;
//end the game
int _end()
{
	cout << "\033[2J\033[1;1H";
	if(B.point<200000)printf("YOU LOSE!\n");
	else printf("YOU WIN!\n");
	printf("Point: %d\n",B.point);
	//turn on the blocking input
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return B.point>=200000;
}
int music_game()
{
	wait_time=1000000,life=3;B.point=0;
	//turn off the blocking input
	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;
	newt.c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	
	//initialize the board
	for(int i=1;i<=maxx;i++)B.refresh();
	B.print(0);
	printf("Press to start...");
	getchar();
	//play
	while(1)
	{
		//set start time
		int st=get_time();
		
		//print without #
		B.print(0);
		
		//check if the knocked note is correct
		char c,cc;
		int flag=1;
		c=getch(wait_time);
		if(c=='0'||(!B.isright(c)))
		{
			flag=0;
			life--;
			if(!life)return _end();
		}
		
		//add to the point
		int diff=(get_time()-st)*1000;
		if(!flag);
		else if(diff<=wait_time/5)B.point+=5000;
		else if(diff<=wait_time/2)B.point+=2000;
		else if(diff<=wait_time)B.point+=1000;
		
		//print with #
		B.print(1);
		B.refresh();
		
		//give out the performance
		if(!flag)printf("Missed...\n");
		else if(diff<=wait_time/5)printf("Perfect!!!\n");
		else if(diff<=wait_time/2)printf("Great!!\n");
		else if(diff<=wait_time)printf("Good!\n");
		
		//check invalid inputs after the first one
		if(wait_time-(get_time()-st)*1000>0)
		{
			cc=getch(wait_time-(get_time()-st)*1000);
			if(cc!='0')
			{
				B.print(0);
				printf("Too early...");
				life--;
				if(!life)return _end();
			}
			if(wait_time/1000-(get_time()-st)>0)usleep(wait_time/1000-(get_time()-st));
		}
		
		//add to the difficulty
		wait_time-=5000;
	}
	
	//reset the input mode
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	return 0;
}