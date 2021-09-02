/*
_____________________________________________________________________________________________________
Course		: CO1302 Programming for Engineers															      
Group		: 2
Year		: 2018/2019
Date		: 20/11/2020 
-----------------------------------------------------------------------------------------------------
                                          GAME PROJECT                                                    
-----------------------------------------------------------------------------------------------------
                                        SKY ATTACK v1.0 
                                            
DEVELOPERS :
01. DIMANTHA L A						- 19_ENG_015			- EN93826
02. KASTHURIARACHCHI K A D G			- 19_ENG_053			- EN93885
03. PUSSADENIYA P M N R					- 19_ENG_082			- EN95142
04. WEERATHUNGA W P T W					- 19_ENG_111			- EN93902
_____________________________________________________________________________________________________
*/

// including headerfiles
#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <fstream>
#include <string.h>
#include <cstdlib>

// defining constants 
#define SCREEN_WIDTH 90 
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define MENU_WIDTH 20
#define GAP_SIZE 7
#define Enemy_DIF 45

using namespace std ; 

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE) ;
COORD CursorPosition ; 

// declaring arrays 
int enemyY[3] ; 
int enemyX[3] ;
int enemyFlag[3] ; 

// gun interface
char GUN[3][5] = { ' ', ' ','±',' ',' ',
					'|','±','±','±','|',
					'±','±','±','±','±' } ;

// initializations
int GUNPos = WIN_WIDTH/2 ; 
int score = 0 ; 
int bullets[20][4] ;
int bulletsLife[20] ;
int bIndex = 0 ; 
int hardness ;

// go to a point directly 
void gotoxy(int x , int y)
{
	CursorPosition.X = x ;
	CursorPosition.Y = y ; 
	SetConsoleCursorPosition(console, CursorPosition) ; 
}

// loading screen
void load()	
{
	system("color 7c") ;
	char a =219 ; 
	gotoxy(52,14);
	cout << "Loading.....\n";
		gotoxy(40,5);cout << "-----------------------------" ;
		gotoxy(40,6);cout << "|      SKY ATTACK v1.0      |" ;
		gotoxy(40,7);cout << "-----------------------------" ;
		gotoxy(31,22);cout << "_______________________________________________________" ;
		gotoxy(31,23);cout << "|     @ 2020 SJP Developers. All rights reserved.     |" ;
		gotoxy(31,24);cout << "|              KASTHURIARACHCHI K A D G               |" ;
		gotoxy(31,25);cout << "|                 WEERATHUNGA W P T W                 |" ;
		gotoxy(31,26);cout << "|                 PUSSADENIYA P M N R                 |" ;
		gotoxy(31,27);cout << "|                    DIMANTHA L A                     |" ;
		gotoxy(31,28);cout << "|_____________________________________________________|" ;
	
		gotoxy(46,16);
	for(int r=1 ; r<=20 ;r++)
	{
		for(int q=0 ; q <=10000000*3;q++);
		cout <<a ;
	}
}

// manage cursor 
void setcursor(bool visible,DWORD size)
{
	if(size == 0)
		size = 20;
	
	CONSOLE_CURSOR_INFO lpCursor; 
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size; 
	SetConsoleCursorInfo(console, &lpCursor); 
}

// game space border
void drawBorder()
{
	for(int i = 0; i < SCREEN_WIDTH; i++)
	{
		gotoxy(i,SCREEN_HEIGHT ); cout << "±" ; 
	}
	for (int i=0 ; i < SCREEN_HEIGHT ; i++)
	{
		gotoxy(0,i); cout << "±" ;
		gotoxy(SCREEN_WIDTH , i ); cout << "±" ;
	}
	for (int i=0 ; i < SCREEN_HEIGHT ; i++)
	{
		gotoxy(WIN_WIDTH, i ); cout << "±" ;
	}	
}

// random enemy generation
void genEnemy(int ind)
{
	enemyX[ind] = 3 + rand()%(WIN_WIDTH-10) ;
} 

// enemy shape
void drawEnemy(int ind)
{
	if (enemyFlag[ind] == true )
	{
		gotoxy(enemyX[ind], enemyY[ind]) ; 		cout << ".==." ;
		gotoxy(enemyX[ind], enemyY[ind]+1) ;	cout << "^^^^" ;
		gotoxy(enemyX[ind], enemyY[ind]+2) ;	cout << "/__\\" ;
		gotoxy(enemyX[ind], enemyY[ind]+3) ; 	cout << ".==." ;
	}	
}

// erasing enemies
void eraseEnemy(int ind)
{
	if(enemyFlag[ind] == true)
	{
	gotoxy(enemyX[ind], enemyY[ind])   ; cout << "    " ;
	gotoxy(enemyX[ind], enemyY[ind]+1) ; cout << "    " ;
	gotoxy(enemyX[ind], enemyY[ind]+2) ; cout << "    " ;
	gotoxy(enemyX[ind], enemyY[ind]+3) ; cout << "    " ;
	}
}

// resetting enemies
void resetEnemy (int ind)
{
	eraseEnemy(ind);
	enemyY[ind] =4 ;
	genEnemy(ind);
}

// bullet generation
void genBullet()
{
	bullets[bIndex][0] = 22 ;
	bullets[bIndex][1] = GUNPos  ;
	bullets[bIndex][2] = 22 ;
	bullets[bIndex][3] = GUNPos +4 ;
	bIndex++ ;
	
	if( bIndex == 20 )
	{
		bIndex = 0 ;
	}	
}

// moving bullet
void moveBullet()
{
	for(int i=0 ; i<20 ; i++)
	{
		if(bullets[i][0] > 2 )
		{
			bullets[i][0]--;
		} else {
			bullets[i][0] = 0 ;
		}

		if(bullets[i][2] > 2) 
		{
			bullets[i][2]--;
		} else {
			bullets[i][2] = 0 ;
		}		
	}
}

// bullet shape
void drawBullets()
{
	for(int i = 0 ; i <20 ; i++)
	{
		if (bullets[i][0] >1)
		{
		gotoxy(bullets[i][1],bullets[i][0]);cout << "^" ;
		gotoxy(bullets[i][3],bullets[i][2]);cout << "^" ;
		}
	}
}

// erasing bullets
void eraseBullets()
{
	for(int i = 0; i<20; i++)
	{
		if(bullets[i][0] >= 1)
		{
		gotoxy(bullets[i][1],bullets[i][0]);cout << " ";
		gotoxy(bullets[i][3],bullets[i][2]);cout << " ";
		}
	}
}

void eraseBullet(int i)
{
		gotoxy(bullets[i][1],bullets[i][0]);cout << " ";
		gotoxy(bullets[i][3],bullets[i][2]);cout << " ";

}

// gun generation
void drawGUN()
{
	for(int i=0; i < 3; i++)
	{
		for(int j = 0 ; j<5 ; j++)
		{
			gotoxy(j+GUNPos, i+22); cout << GUN[i][j];
		}
	}
}

// erasing gun
void eraseGUN()
{
	for(int i=0; i<3; i++)
	{
		for(int j = 0; j<5; j++)
		{
			gotoxy(j+GUNPos, i+22); cout<<" ";
		}
	}
}

// checking gun and enemy collision
int collision()
{
	if (enemyY[0]+4 >= 23)
	{
		if(enemyX[0] + 4 - GUNPos >= 0 && enemyX[0] + 4 - GUNPos <8)
		{
			return 1 ;
		}
	}
	return 0 ;
}

// checking bullet and enemy collision
int bulletHit() 
{
	for(int i=0; i<20;i++)
	{
		for (int j=0; j <4; j+=2)
		{
			if( bullets[i][j] != 0 )
			{
				if (bullets[i][j] >= enemyY[0] && bullets[i][j] <= enemyY[0]+4 )
				{
					if(bullets[i][j+1] >= enemyX[0] && bullets[i][j+1] <= enemyX[0]+4) 
					{
						eraseBullet(i);
						bullets[i][j] = 0 ; 
						resetEnemy(0) ;
						return 1 ;
					}
				}
				if (bullets[i][j] >= enemyY[1] && bullets[i][j] <= enemyY[1]+4 )
				{
					if(bullets[i][j+1] >= enemyX[1] && bullets[i][j+1] <= enemyX[1]+4) 
					{
						eraseBullet(i);
						resetEnemy(1);
						bullets[i][j] = 0 ; 
						return 1 ;
					}
				}
			}
		}
	}
	return 0;
}

// generate current time and date 
string getCurrentTimenDate() 			
{
	//taking current date and time to save records in record.txt ; 
	//declaring argumnet for time()
	time_t tt; 
	//declaring variable to store return value of local time() ;
	struct tm*ti ; 
	//applyig time()
	time(&tt); 
	//using local time() 
	ti= localtime(&tt) ; 
	
	return asctime(ti) ;
}

// displaying scores										
void score_Display()
{
	system("cls"); 
		gotoxy(40,5);cout << "-----------------------------" ;
		gotoxy(40,6);cout << "|        SCORE BOARD        |" ;
		gotoxy(40,7);cout << "-----------------------------" ;
		gotoxy(10,10);cout << "Your Score : " << score ;
		gotoxy(10,12);cout << "Enter your Name : "  ;

	char user_name[30] ;
	cin >> user_name ; 
	
	ofstream outFile;
	outFile.open("score.txt") ;		// save game details(score, player name, time&date) to score.txt 		

	outFile << score << "       "<< user_name << "       "<< getCurrentTimenDate() <<"\n"  ;
	
	outFile.close() ; 


	ifstream infile ; 
	int user_lasthighscore =0; 
		 
	infile.open("highscore.txt"); 		// reading highscore.txt to get previous high score records 
	
		int last_highscore ;
		while ( infile >> last_highscore  )	
	{
		user_lasthighscore   = last_highscore ;		// saving last highscore data from highscore.txt to user_lasthighscore variable 
	}
	infile.close() ; 
											
	if (score > user_lasthighscore )	// comparing game score with last high score 
	{ 									// score > last highscore; then it should be printed and assigned to variables
	system("cls"); 
	gotoxy(40,5);cout << "-----------------------------" ;
	gotoxy(40,6);cout << "|        HALL OF FAME       |" ;
	gotoxy(40,7);cout << "-----------------------------" ;
	gotoxy(10,10);cout << "---------------------------------------------------------------" ;
	gotoxy(10,12);cout << "	  Congratulations! New high score :) " ;
	gotoxy(10,14);cout << "   Player      : " <<user_name ;
	gotoxy(10,15);cout << "   Score       : " <<score ;
	gotoxy(10,16);cout << "   Time & Date : " << getCurrentTimenDate() ;
	gotoxy(10,18);cout << "---------------------------------------------------------------" ;
												
	ofstream update;				// updating new highscore ; 
	update.open("highscore.txt") ;

	update << score << "       "<< user_name << "       "<< getCurrentTimenDate() <<"\n"  ;
	
	update.close() ; 
	
	Sleep(7000) ;
	}
	
	else if (score < user_lasthighscore || score == user_lasthighscore ) 	// if score <= last high score 
	{
	system("cls"); 
	
	gotoxy(40,5);cout << "-----------------------------" ;
	gotoxy(40,6);cout << "|        HALL OF FAME       |" ;
	gotoxy(40,7);cout << "-----------------------------" ;
	gotoxy(10,10);cout << "---------------------------------------------------------------" ;
	gotoxy(10,11);cout << "Current high score details " ;
	gotoxy(10,12);
	
	// taking last high score records from highcore.txt 
	string line_ ; 
	ifstream file_("highscore.txt") ; 
	if (file_.is_open() )
	while (getline(file_,line_))
	{
		cout << line_  ; 
	}
	file_.close() ;
		
	gotoxy(10,15);cout << " Next time you can beat the highscore :) " ;
	gotoxy(10,17);cout << "   Player      : " <<user_name ;
	gotoxy(10,18);cout << "   Score       : " <<score ;
	gotoxy(10,20);cout << "---------------------------------------------------------------" ;
				
	Sleep(7000) ;
	}
}

// game over screen
void gameover()	
{
	system("cls");
	cout << endl;
	cout <<"\t\t_____________________________________________________"<<endl;
	cout <<"\t\t                                                     "<<endl;
	cout <<"\t\t                      GAME OVER                      " << endl;
	cout <<"\t\t_____________________________________________________" <<endl<<endl;
	cout <<"\t\tYou will be directed to the score board in 3 seconds"; 
	cout << "." ; Sleep (1000) ; 
	cout << "." ; Sleep (1000) ; 
	cout << "." ; Sleep (1000) ; 
	
	score_Display() ;
}

// updating score
void updateScore()
{
	gotoxy(WIN_WIDTH + 6 ,5) ; cout << "Score : " <<score<<endl;
}

// instruction display
void instructions() 
{
	system("cls"); 
	gotoxy(40,5);cout << "-----------------------------" ;
	gotoxy(40,6);cout << "|       INSTRUCTIONS        |" ;
	gotoxy(40,7);cout << "-----------------------------" ;
	gotoxy(10,10);cout << "---------------------------------------------------------------" ;
	gotoxy(10,12);cout << " Press SPACEBAR to shoot.  " ;
	gotoxy(10,13);cout << " Use [<] , [>] keys to move the gun to left and right. " ;
	gotoxy(10,14);cout << " If an enemy hit the gun then the game will end.  " ;
	gotoxy(10,15);cout << " You can score marks by shooting enemies, 1 mark for one kill.  " ;
	gotoxy(10,18);cout << "_______________________________________________________________" ;
	gotoxy(10,20);cout << " << Press any key to go back to menu  " ;
	gotoxy(10,22);cout << "---------------------------------------------------------------" ;

	getch() ; 
		
}

// gameplay 
void play (int hardness)
{
	GUNPos = -1 + WIN_WIDTH/2 ;
	score = 0 ;
	enemyFlag[0] = 1 ; 
	enemyFlag[1] = 1 ;
	enemyY[0] = enemyY[1] = 4 ; 
	
	for(int i=0; i <20 ; i++)
	{
		bullets[i][0] = bullets[i][1] = 0 ; 
	}
	system("cls") ; 
	drawBorder();
									
					
	genEnemy(0);
	genEnemy(1) ;

	updateScore() ;
	
		gotoxy(WIN_WIDTH + 5 , 2); cout << "SKY ATTACK" ; 
		gotoxy(WIN_WIDTH + 4 , 4); cout << "-------------" ; 
		gotoxy(WIN_WIDTH + 4 , 6); cout << "-------------" ; 
		gotoxy(WIN_WIDTH + 3 , 12); cout << " Controls " ; 
		gotoxy(WIN_WIDTH + 3 , 13); cout << "----------" ; 
		gotoxy(WIN_WIDTH + 2 , 14); cout << "< key - left" ;
		gotoxy(WIN_WIDTH + 2 , 15); cout << "> key - right" ; 
		gotoxy(WIN_WIDTH + 2 , 16); cout << "Spacebar - shoot" ; 
		gotoxy(WIN_WIDTH + 2 , 17); cout << "ESC - quit" ; 
		
		
		gotoxy(10,5); cout << "Press any key to start" ; 
		getch();
		gotoxy(10,5);cout << "                         ";
		
		while(1)
		{
			if(kbhit())
			{
				char ch = getch();
				if(ch == ',') 			// moving gun to left when [<] is pressed
				{
					if (GUNPos > 2)
					{
						GUNPos -= 2;
					}	
				}
				if(ch == '.')			// moving gun to right when [>] is pressed
				{
					if (GUNPos < WIN_WIDTH-7)
					{
						GUNPos += 2 ;
					}
				}
				if(ch==32)				// bullet generation when spacebar is pressed
				{
					genBullet();
				}
				if(ch==27)				// quiting when ESC is pressed
				{
					break;
				}
			}
			
			drawGUN();
			
			drawEnemy(0);				
			drawEnemy(1);
			
			drawBullets(); 
			
			if (collision() == 1)  
			{
				gameover();
				return;
			}
			if(bulletHit() == 1)
			{
				score++;
				updateScore() ;
			}
			
			// hardness ajustment											
			if	    (hardness == 1) {Sleep(200) ;} 
			else if (hardness == 2) {Sleep(150) ;} 
			else if (hardness == 3) {Sleep(100) ;} 
			
			eraseGUN();
			eraseEnemy(0);
			eraseEnemy(1);
			eraseBullets();
			moveBullet() ;
			
			if (enemyFlag[0] == 1)
			{
				enemyY[0] +=1; 
			}
			
			if (enemyFlag[1] == 1)
			{
				enemyY[1] +=1; 
			}
			
			if (enemyY[0] > SCREEN_HEIGHT-5)
			{
				resetEnemy(0); 
			}
			if (enemyY[1] > SCREEN_HEIGHT-5)
			{
				resetEnemy(1); 
			}
			
		}
		
}

// quit option display and exit
void exitprogram ()
{
		system("cls");	
		gotoxy(40,5);cout << "-----------------------------" ;
		gotoxy(40,6);cout << "|         GOOD BYE !        |" ;
		gotoxy(40,7);cout << "-----------------------------\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" ;
		
	exit(0);
} 

// hardness menu
void mode_menu() 
{
	do
	{
		system("cls");	
		gotoxy(40,5);cout << "-----------------------------" ;
		gotoxy(40,6);cout << "|      CHOOSE A LEVEL       |" ;
		gotoxy(40,7);cout << "-----------------------------" ;
		gotoxy(45,9);cout  << "1. Easy" ;
		gotoxy(45,10);cout << "2. Medium" ;
		gotoxy(45,11);cout << "3. Hard" ;
		gotoxy(45,12);cout << "4. << Back to main menu" ;
		gotoxy(43,14);cout << "Select option" ;
	
		char op = getche() ; 
	
		if(op == '1')
		{
			hardness = 1 ; 
			play(hardness );		// easy mode
			break ; 
		}
		
		else if(op == '2') 
		{
			
			hardness = 2 ; 
			play(hardness );		// medium mode
			break ; 	
		}
		
		else if(op == '3')
		{
			hardness = 3 ; 
			play(hardness );		//  hard mode
			break ; 
		}
		
		else if(op == '4')
		{
			break ;				//  return to main menu
		}	
				
	} while(1);
	
}

// main function
int main() 
{
setcursor(0,0) ;			//initializing the cursor at 0,0

srand((unsigned)time(NULL)) ; 	
	
	load() ;					// loading screen
	Sleep(250);
	system("color 0F") ; 		// changing colors to normal
		
	// main menu displaying						
	do
	{
		system("cls");	
		gotoxy(40,5);cout << "-----------------------------" ;
		gotoxy(40,6);cout << "|      SKY ATTACK v1.0      |" ;
		gotoxy(40,7);cout << "-----------------------------" ;
		gotoxy(45,9);cout  << "1. Start Game" ;
		gotoxy(45,10);cout << "2. Instructions" ;
		gotoxy(45,11);cout << "3. Quit" ;
		gotoxy(43,13);cout << "Select option" ;
		
		gotoxy(31,22);cout << "_______________________________________________________" ;
		gotoxy(31,23);cout << "|     @ 2020 SJP Developers. All rights reserved.     |" ;
		gotoxy(31,24);cout << "|              KASTHURIARACHCHI K A D G               |" ;
		gotoxy(31,25);cout << "|                 WEERATHUNGA W P T W                 |" ;
		gotoxy(31,26);cout << "|                 PUSSADENIYA P M N R                 |" ;
		gotoxy(31,27);cout << "|                    DIMANTHA L A                     |" ;
		gotoxy(31,28);cout << "|_____________________________________________________|" ;
	
	
		char op = getche() ; 
	
		if(op == '1')
		{
			mode_menu()  ;		// going to mode menu 
		}
		else if(op == '2') 
		{
			instructions();		// displaying instructions
		}
		else if(op == '3')
		{
			exitprogram() ;		// quiting game
		}			
		
	} while(1); 
	
	return 0;
		
}



