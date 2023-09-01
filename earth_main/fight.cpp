#include <bits/stdc++.h>
#include <unistd.h>
#include <thread>
#define RESET   "\033[0m"
#define RED     "\033[1;31m"
#define GREEN   "\033[1;32m"
#define YELLOW  "\033[1;33m"
#define BLUE    "\033[1;34m"
#define MAGENTA "\033[1;35m"
#define CYAN    "\033[1;36m"
using namespace std;
//the size of the character image
const int MAXN=30,MAXM=100;
//the distance between the characters
const int delta=50;
//the original hp of two entities
const int comethp=50000,herohp=5000;
//define the class of characters
class entity{
	public:
		int HP,MP,PRO;
		int pos;
		char fig[MAXN][MAXM];
		entity(int _HP,int _MP,int _PRO,int _pos)
		{
			
			HP=_HP;MP=_MP;PRO=_PRO,pos=_pos;
			for(int i=0;i<MAXN;i++)
			{
				for(int j=0;j<MAXM;j++)
				{
					fig[i][j]=' ';
				}
			}
			
		}
};
entity hero(herohp,100,90,0);
entity enemy(comethp,100,70,delta);
//initialize the figure of two character
void init()
{
	ifstream fin;
	fin.open("hero.txt");
	string s;int tot=0;
	while(getline(fin,s))
	{
		for(int i=0;i<s.length();i++)hero.fig[tot][i]=s[i];
		tot++;
	}
	fin.close();
	fin.open("enemy.txt");
	tot=0;
	while(getline(fin,s))
	{
		for(int i=0;i<s.length();i++)enemy.fig[tot][i]=s[i];
		tot++;
	}
	fin.close();
}
//print the HP bar
void print_bar()
{
	string s;
	s.clear();
	for(int i=0;i<hero.HP*20/herohp;i++)s+="\u2588";
	for(int i=hero.HP*20/herohp;i<10;i++)s+="";
	if(hero.HP*20/herohp>=18)cout<<GREEN;
	else if(hero.HP*20/herohp>=8)cout<<YELLOW;
	else cout<<RED;
	cout<<left<<setw(delta-5)<<s<<RESET;
	s.clear();
	for(int i=0;i<enemy.HP*50/comethp;i++)s+="\u2588";
	for(int i=enemy.HP*50/comethp;i<10;i++)s+="";
	if(enemy.HP*50/comethp>=45)cout<<GREEN;
	else if(enemy.HP*50/comethp>=20)cout<<YELLOW;
	else cout<<RED;
	cout<<"                                   "<<s<<RESET<<endl;
}
//print the current status
void print()
{
	system("clear");
	cout<<"     "<<left<<setw(delta-5)<<"Your HP: "+to_string(hero.HP);
	cout<<"               "<<"Comet's HP: "<<enemy.HP<<endl;
	cout<<"     "<<left<<setw(delta-5)<<"Your MP: "+to_string(hero.MP)<<endl;
	print_bar();
	for(int i=0;i<30;i++)
	{
		for(int j=0;j<enemy.pos+100;j++)
		{
			if(j>=hero.pos&&j<enemy.pos)
			{
				cout<<hero.fig[i][j-hero.pos];
			}
			else if(j>=enemy.pos)
			{
				cout<<enemy.fig[i][j-enemy.pos];
			}
			else cout<<' ';
		}
		cout<<endl;
	}
}
//generate random number
int get(int l,int r)
{
	return rand()%(r-l+1)+l;
}
//print the movement of character
void move(entity &a,int d)
{
	print();
	usleep(500000);
	a.pos+=d;
	print();
	a.pos-=d;
	usleep(500000);
	print();
}
//apply the attack
void attk(entity &a,entity &b,int damage,int d)
{
	if(get(1,100)>a.PRO)
	{
		print();
		usleep(500000);
		a.pos+=d;
		print();
		a.pos-=d;
		usleep(500000);
		print();
		cout<<GREEN<<"MISS!"<<RESET<<endl;
		usleep(1000000);
		return;
	}
	damage=damage+damage*get(-2000,2000)/10000;
	print();
	usleep(500000);
	a.pos+=d;
	b.HP-=damage;
	print();
	a.pos-=d;
	usleep(500000);
	print();
	cout<<RED<<"DAMAGE: "<<damage<<RESET<<endl;
	usleep(1000000);
	return;
}
//realize the blink effect
static void blink(string text, int blink_interval)
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
//check whether MP is enough
bool check(entity &a,int MP)
{
	if(a.MP<MP)
	{
		cout<<RED<<"NO ENOUGH MP"<<endl<<RESET;
		usleep(1000000);
		return 0;
	}
	a.MP-=MP;
	return 1;
}
int dele()
{
	int cnt=0;
	for(int i=0;i<MAXN;i++)
	{
		for(int j=0;j<MAXM;j++)
		{
			if(enemy.fig[i][j]!=' ')cnt++;
		}
	}
	if(cnt<50)return 0;
	for(int i=0;i<MAXN;i++)
	{
		for(int j=0;j<MAXM;j++)
		{
			if(enemy.fig[i][j]!=' '&&get(1,10)>=9)
			{
				enemy.fig[i][j]=' ';
			}
		}
	}
	return 1;
}
void BOMB()
{
	print();
	printf("The comet is preparing for a big bomb!!!!!!!!!!!!\n");
	usleep(1500000);
	printf("Are you ready?\n");
	usleep(1500000);
	printf("3\n");
	usleep(1000000);
	printf("2\n");
	usleep(1000000);
	printf("1\n");
	usleep(1000000);
	system("clear");
	int cnt=0;
        while((++cnt)<=1000)printf("BOMB!!!!!!!!!!!!!!\n"),usleep(1000);
        system("clear");
        hero.HP-=herohp*2/5;
        enemy.HP=1;
        for(int i=0;i<MAXN;i++)
        {
        	for(int j=0;j<MAXM;j++)
        	{
        		enemy.fig[i][j]=' ';
        	}
        }
        enemy.fig[MAXN/2][MAXN/2]='@';
        enemy.fig[MAXN/2-1][MAXN/2-1]='@';
        enemy.fig[MAXN/2-1][MAXN/2]='@';
        enemy.fig[MAXN/2][MAXN/2-1]='@';
        print();
        usleep(2000000);
}
int fight()
{
	srand(time(NULL));
	entity tmpa(herohp,100,90,0),tmpb(comethp,100,70,delta);
	hero=tmpa,enemy=tmpb;
	init();
	//the main process
	int tick=0;
	while(hero.HP>0&&enemy.HP>0)
	{
		if(tick==0)enemy.PRO=70;
		print();
		printf("Choose you skill to attack the Comet King\n");
		printf("[1] Kick (0 MP)	[2] Huge Kick (20 MP)	[3] Seduce by Your Body (50 MP)");
		printf("	[4] Drink Water (50 MP)\n");
		char opt;
		system("stty -icanon");
		cin>>opt;
		system("stty icanon");
		if(opt=='1')
		{
			attk(hero,enemy,comethp/100,10);
		}
		else if(opt=='2')
		{
			if(check(hero,20))attk(hero,enemy,comethp/25,15);
			else continue;
		}
		else if(opt=='3')
		{
			if(!check(hero,50))continue;
			attk(hero,enemy,0,20);
			tick=3;
			enemy.PRO=0;
		}
		else if(opt=='4')
		{
			if(!check(hero,50))continue;
			hero.HP+=herohp/25;
			print();
			printf("Your HP recovered by %d.\n",herohp/25);
			usleep(1000000);
		}
		else 
		{
			system("clear");
			string message = "Invalid input, please try again!";
			int blink_time = 500;	// unit is milliseconds
			blink(message, blink_time);
			cout << endl << endl;
			continue;
		}
		//enemy's turn
		if(enemy.HP<=0)break;
		if(enemy.HP==1)
		{
			print();
			printf("The comet is very very weak...\n");
			usleep(1500000);
			continue;
		}
		if(enemy.HP<=comethp/17)
		{
			BOMB();
                        continue;
		}
		opt=get(1,12);
		if(opt==12)
		{
			enemy.HP+=comethp/25;
			print();
			printf("The comet's HP recovered by %d.\n",comethp/25);
			usleep(1500000);
		}
		else if(opt>=9)
		{
			print();
			printf("The comet throws part of its body to you!!\n");
			usleep(1500000);
			if(dele())enemy.HP-=comethp/20,attk(enemy,hero,herohp/25,-20);
			else printf("But no enough body...\n"),usleep(1000000);
		}
		else 
		{
			print();
			printf("The comet strikes on you!\n");
			usleep(1500000);
			attk(enemy,hero,herohp/50,-10);
		}
		hero.MP=min(hero.MP+10,100);
		if(tick)tick--;
	}
	if(hero.HP<=0)
	{
		printf("YOUR DIED!\n");
		return 0;
	}
	printf("YOUR WIN! PRESS ENTER TO CONTINUE\n");
	return 1;
}
