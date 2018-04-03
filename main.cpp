#include "curses.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <cstdlib>


//int kolumny = 0;
//int rzedy = 0;
//char tekst[] = "Wyswietlany tekst!";
bool sztucce[5] = { 0, 0, 0, 0, 0 };
char sztucceC[5] = { 'W', 'W', 'W', 'W', 'W' };
float progres[5] = { 5, 7, 6, 9, 2 };
bool stan[5] = { 0, 0, 0, 0, 0 };
int glod[5] = { 0, 0, 0, 0, 0 };
//string name[5];//= { "SOKRATES", "PLATON", "ARYSTOTELES", "EPIKUR", "ZENON" };
//name[0] = "SOKRATES";
//string color[5]={"COLOR_RED"};


using namespace std;

class FILOZOF{

public:
	FILOZOF(int a, int b,int c,char d);
	int szt[2];
	char ch;
	int licznik;
	void operator()(){
		while (true){
			if (sztucce[szt[0]] == false && sztucce[szt[1]] == false){
				sztucce[szt[0]] = true;
				sztucce[szt[1]] = true;
				sztucceC[szt[0]] = ch;
				sztucceC[szt[1]] = ch;
				glod[licznik] = 0;

				stan[licznik] = true;
				while (progres[licznik] != 0){
					Sleep(250);
					progres[licznik] = progres[licznik] - 0.25;
				}
				sztucce[szt[0]] = false;
				sztucce[szt[1]] = false;
				sztucceC[szt[0]] = 'W';
				sztucceC[szt[1]] = 'W';
				stan[licznik] = false;
				
				progres[licznik] = (rand()%5)+5;
				
			}
			
				while (progres[licznik] != 0){
					Sleep(250);
					progres[licznik]=progres[licznik]-0.25;
				}
				progres[licznik] = (rand() % 5) + 5;
				glod[licznik] = glod[licznik] + progres[licznik];
			}
		
	}

};

FILOZOF::FILOZOF(int  a, int  b, int c,char d){
	szt[0] = a;
	szt[1] = b;
	licznik = c;
	ch = d;
}
char k='l';
void check(){
	while (true){
		k = getch();
	}
}

int main(){

	srand(time(NULL));


	
	FILOZOF f1(0, 1,0,'R');
	FILOZOF f2(1, 2,1,'Y');
	FILOZOF f3(2, 3, 2,'G');
	FILOZOF f4(3, 4, 3,'B');
	FILOZOF f5(4, 0, 4,'C');

	thread t1(f1);
	thread t2(f2);
	thread t3(f3);
	thread t4(f4);
	thread t5(f5);
	
	thread cyk(check);
	

	try{



	int i = 0;
	initscr(); //Start
	if (has_colors() == TRUE) //1
	{
		//char k;
		while (k!='q')
		{
	
			start_color(); //2
			init_pair(1, COLOR_WHITE, COLOR_BLACK); //3
		
			attron(COLOR_PAIR(1)); //4
			printw("%c  ", k);
			printw("SO2 PROJEKT - FILZOFOWIE \t");
			attron(A_BOLD);
	
			printw("Czas: %.2f s", (float)i / 4);
			attroff(A_BOLD);
			printw("\n\nSZTUCCE: ");
			for (int j = 0; j < 5; j++){


			
				if (sztucceC[j] == 'R'){
					attroff(COLOR_PAIR(1));
					init_pair(2, COLOR_RED, COLOR_BLACK);
					attron(COLOR_PAIR(2));
					printw(" %d ", j);
					attroff(COLOR_PAIR(2));
				}
				else if (sztucceC[j] == 'Y'){
					attroff(COLOR_PAIR(1));
					init_pair(3, COLOR_YELLOW, COLOR_BLACK);
					attron(COLOR_PAIR(3));
					printw(" %d ", j);
					attroff(COLOR_PAIR(3));
				}
				else if (sztucceC[j] == 'G'){
					attroff(COLOR_PAIR(1));
					init_pair(4, COLOR_GREEN, COLOR_BLACK);
					attron(COLOR_PAIR(4));
					printw(" %d ", j);
					attroff(COLOR_PAIR(4));
				}
				else if (sztucceC[j] == 'B'){
					attroff(COLOR_PAIR(1));
					init_pair(5, COLOR_BLUE, COLOR_BLACK);
					attron(COLOR_PAIR(5));
					printw(" %d ", j);
					attroff(COLOR_PAIR(5));
				}
				else if (sztucceC[j] == 'C'){
					attroff(COLOR_PAIR(1));
					init_pair(6, COLOR_CYAN, COLOR_BLACK);
					attron(COLOR_PAIR(6));
					printw(" %d ", j);
					attroff(COLOR_PAIR(6));
				}
				else if (sztucceC[j] == 'W'){
					printw(" %d ", j);
				}
				
			}
			init_pair(1, COLOR_WHITE, COLOR_BLACK);
			attron(COLOR_PAIR(1));
			printw("\n\n\nFILOZOFOWIE: \tCZYNNOSC\tPROGRES\tGLOD");
			attroff(COLOR_PAIR(1));

			//SOKRATES
			init_pair(2, COLOR_RED, COLOR_BLACK);
			attron(COLOR_PAIR(2));
			printw("\n\nSOKRATES: \t");
			if (stan[0] == false){
				printw("medytuje");
			}
			else{
				printw("je\t");
			}
				printw("\t%.2f s",progres[0]);
				printw("\t %d s", glod[0]);
			attroff(COLOR_PAIR(2));

			//PLATON
			init_pair(3, COLOR_YELLOW, COLOR_BLACK);
			attron(COLOR_PAIR(3));
			printw("\n\nPLATON: \t");
			if (stan[1] == false){
				printw("medytuje");
			}
			else{
				printw("je\t");
			}
			printw("\t%.2f s", progres[1]);
			printw("\t %d s",glod[1]);
			attroff(COLOR_PAIR(3));

			//ARYSTOTELES
			init_pair(4, COLOR_GREEN, COLOR_BLACK);
			attron(COLOR_PAIR(4));
			printw("\n\nARYSTOTELES: ");
			if (stan[2] == false){
				printw("\tmedytuje");
			}
			else{
				printw("\tje\t");
			}
			printw("\t%.2f s", progres[2]);
			printw("\t %d s", glod[2]);
			attroff(COLOR_PAIR(4));

			//EPIKUR
			init_pair(5, COLOR_BLUE, COLOR_BLACK);
			attron(COLOR_PAIR(5));
			printw("\n\nEPIKUR: ");
			if (stan[3] == false){
				printw("\tmedytuje");
			}
			else{
				printw("\tje\t");
			}
			printw("\t%.2f s", progres[3]);
			printw("\t %d s", glod[3]);
			attroff(COLOR_PAIR(5));

			//ZENON
			init_pair(6, COLOR_CYAN, COLOR_BLACK);
			attron(COLOR_PAIR(6));
			printw("\n\nZENON: \t");
			if (stan[4] == false){
				printw("\tmedytuje");
			}
			else{
				printw("\tje\t");
			}
			printw("\t%.2f s", progres[4]); 
			printw("\t %d s", glod[4]);
			attroff(COLOR_PAIR(6)); //Wy³¹czenie koloru tekstu
			//attroff(COLOR_PAIR(2));
			 //1

			Sleep(250);
			refresh();
			clear();
			i++;
			if (k == 'a'){
				
	/*			if (t1.joinable()){
					t1.join();
					//throw;
				}
				if (t2.joinable()){
					t2.join();
					//throw;
				}
				if (t3.joinable()){
					t3.join();
					//throw;
				}
				if (t4.joinable()){
					t4.join();
					//throw;
				}*/
				if (t5.joinable()){
					
					t5.join();
				//	t5.~thread();
					throw;
				//}
//				if (cyk.joinable()){
//					cyk.join();
//				}
				
				k = 'l';

			}

		}

		printw("END");
		getch();
		endwin(); //koniec
		return 0;


		//getmaxyx(stdscr, rzedy, kolumny);
		//wyswietlanie tekstu
		//mvprintw(rzedy / 2, (kolumny / 2) - (sizeof(tekst) / 2), tekst); //2
		//getch();
	}
	else
	{
		printw("Twoja Konsolka nie obsluguje kolorow. :/ ");
	}
	}
	catch (...){
		


		
	}
	return 0;
}