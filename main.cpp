#include "curses.h"
#include <iostream>
#include <Windows.h>
#include <thread>
#include <cstdlib>
#include <semaphore.h>
#include <pthread.h>

#define NUMBER_OF_PHILOSOPHERS 5

bool sztucce[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char sztucceC[10] = { 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W', 'W' };
float progres[10] = { 5, 7, 6, 9, 2, 8,	2,	5,	6,	4 };
int stan[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
float glod[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
char kolor[10] = { 'R', 'Y', 'G', 'B', 'C', 'R', 'Y', 'G', 'B', 'C' };
bool fin = false;

using namespace std;

sem_t waiter;
sem_t fork[NUMBER_OF_PHILOSOPHERS];
pthread_t philosophers[NUMBER_OF_PHILOSOPHERS];


class FILOZOF{

public:
	FILOZOF();
	FILOZOF(int a);
	int index;
	void *life(void){

		while (true){

			if (fin){
				break;
			}

			//
			//myœlenie 
			//


			stan[index] = 0;

			while (progres[index] != 0){
				Sleep(250);
				progres[index] = progres[index] - 0.25;
			}

		

			//
			//czekanie na kelenra
			//
			stan[index] = 1;

			progres[index] = 1;
			while (progres[index])
			{
				
				Sleep(250);
				progres[index] = progres[index] - 0.25;
			}

			

			sem_wait(&waiter);
			//
			//siedzi przy stole
			//

			stan[index] = 2;
			int right = (index + 1) % NUMBER_OF_PHILOSOPHERS;
			int left = (index) % NUMBER_OF_PHILOSOPHERS;
			progres[index] = 1;
			while (progres[index])
			{

				Sleep(250);
				progres[index] = progres[index] - 0.25;
			}
			

			sem_wait(&fork[right]);
			sem_wait(&fork[left]);

			sztucce[right] = true;
			sztucce[left] = true;
			sztucceC[right] = kolor[index];
			sztucceC[left] = kolor[index];

			//
			//jedzenie
			//

			progres[index] = (rand() % 5) + 5;

			

					stan[index] = 3;
					while (progres[index] != 0){
						Sleep(250);
						progres[index] = progres[index] - 0.25;
					}
			//
			//odkladanie sztuccy
			//
					stan[index] = 4;
					progres[index] = 0.5;
					while (progres[index] != 0){
						Sleep(250);
						progres[index] = progres[index] - 0.25;
					}
				

					sztucce[right] = false;
					sztucce[left] = false;
					sztucceC[right] = 'W';
					sztucceC[left] = 'W';

					sem_post(&fork[left]);
					sem_post(&fork[right]);
					sem_post(&waiter);



				
				stan[index] = 0;
				progres[index] = (rand() % 5) + 5;

		}
		
		
	}

	static void *exe(void *context){

		return ((FILOZOF *)context)->life();
	}
};

FILOZOF::FILOZOF(int  a){
	index = a;

}

FILOZOF::FILOZOF(){
	index = NULL;
}

char p='a';
bool elo = false;

void* check(void *){
	do{
		p = getch();

		
	} while (p != 'q');

	fin = true;
	return NULL;
}




int main(){

	srand(time(NULL));


	FILOZOF filo[NUMBER_OF_PHILOSOPHERS];

	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; i++){

		filo[i] = FILOZOF(i);

	}


	sem_init(&waiter, 0, NUMBER_OF_PHILOSOPHERS - 1);

	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		sem_init(&fork[i], 0, 1);
	}

	pthread_t cyk;

	pthread_create(&cyk, NULL, check, NULL);

	for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
		pthread_create(&philosophers[i], NULL, &FILOZOF::exe, &filo[i]);
	}





	//try{


	int i = 0;
	initscr(); //Start
		if (has_colors() == TRUE) //1
		{

			while (true){
						
				start_color(); //2
				init_pair(1, COLOR_WHITE, COLOR_BLACK); //3
		
				attron(COLOR_PAIR(1)); //4
				printw("SO2 PROJEKT - FILZOFOWIE \t");
				attron(A_BOLD);
	
				printw("Czas: %.2f s", (float)i / 4);
				attroff(A_BOLD);
				printw("\n\nSZTUCCE: ");
				for (int j = 0; j < NUMBER_OF_PHILOSOPHERS; j++){


			
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
				printw("\n\n\nFILOZOFOWIE: \tCZYNNOSC\t\t\tPROGRES\tGLOD");
				attroff(COLOR_PAIR(1));

				//SOKRATES
				init_pair(2, COLOR_RED, COLOR_BLACK);
				attron(COLOR_PAIR(2));
				printw("\n\nSOKRATES: \t");
				if (stan[0] == 0){
					printw("medytuje\t");
				}
				else if (stan[0] == 1){
					printw("czeka na kelnera");
				}
				else if (stan[0]==2)
				{
					printw("siedzi przy stole");
				}
				else if (stan[0]==3){
					printw("je\t\t");
				}
				else if (stan[0] == 4){
					printw("oddklada sztucce");
				}
					printw("\t\t%.2f s",progres[0]);
					printw("\t %.2f s", glod[0]);
				attroff(COLOR_PAIR(2));

				//PLATON
				init_pair(3, COLOR_YELLOW, COLOR_BLACK);
				attron(COLOR_PAIR(3));
				printw("\n\nPLATON: \t");
				if (stan[1] == 0){
					printw("medytuje\t");
				}
				else if (stan[1] == 1){
					printw("czeka na kelnera");
				}
				else if (stan[1] == 2)
				{
					printw("siedzi przy stole");
				}
				else if (stan[1] == 3){
					printw("je\t\t");
				}
				else if (stan[1] == 4){
					printw("oddklada sztucce");
				}
				printw("\t\t%.2f s", progres[1]);
				printw("\t %.2f s",glod[1]);
				attroff(COLOR_PAIR(3));

				//ARYSTOTELES
				init_pair(4, COLOR_GREEN, COLOR_BLACK);
				attron(COLOR_PAIR(4));
				printw("\n\nARYSTOTELES: ");
				if (stan[2] == 0){
					printw("\tmedytuje\t");
				}
				else if (stan[2] == 1){
					printw("\tczeka na kelnera");
				}
				else if (stan[2] == 2)
				{
					printw("\tsiedzi przy stole");
				}
				else if (stan[2] == 3){
					printw("\tje\t\t");
				}
				else if (stan[2] == 4){
					printw("\toddklada sztucce");
				}
				printw("\t\t%.2f s", progres[2]);
				printw("\t %.2f s", glod[2]);
				attroff(COLOR_PAIR(4));

				//EPIKUR
				init_pair(5, COLOR_BLUE, COLOR_BLACK);
				attron(COLOR_PAIR(5));
				printw("\n\nEPIKUR: ");
				if (stan[3] == 0){
					printw("\tmedytuje\t");
				}
				else if (stan[3] == 1){
					printw("\tczeka na kelnera");
				}
				else if (stan[3] == 2)
				{
					printw("\tsiedzi przy stole");
				}
				else if (stan[3] == 3){
					printw("\tje\t\t");
				}
				else if (stan[3] == 4){
					printw("\toddklada sztucce");
				}
				printw("\t\t%.2f s", progres[3]);
				printw("\t %.2f s", glod[3]);
				attroff(COLOR_PAIR(5));

				//ZENON
				init_pair(6, COLOR_CYAN, COLOR_BLACK);
				attron(COLOR_PAIR(6));
				printw("\n\nZENON: \t");
				if (stan[4] == 0){
					printw("\tmedytuje\t");
				}
				else if (stan[4] == 1){
					printw("\tczeka na kelnera");
				}
				else if (stan[4] == 2)
				{
					printw("\tsiedzi przy stole");
				}
				else if (stan[4] == 3){
					printw("\tje\t\t");
				}
				else if (stan[4] == 4){
					printw("\toddklada sztucce");
				}
				printw("\t\t%.2f s", progres[4]); 
				printw("\t %.2f s", glod[4]);
				attroff(COLOR_PAIR(6)); //Wy³¹czenie koloru tekstu
				//attroff(COLOR_PAIR(2));
				 //1

				if (NUMBER_OF_PHILOSOPHERS > 5){

					for (int u = 5; u < NUMBER_OF_PHILOSOPHERS; u++){
						init_pair(2, COLOR_RED, COLOR_BLACK);
						attron(COLOR_PAIR(2));
						printw("\n\%d %c: \t\t", u,kolor[u]);
						if (stan[u] == 0){
							printw("medytuje\t");
						}
						else if (stan[u] == 1){
							printw("czeka na kelnera");
						}
						else if (stan[u] == 2)
						{
							printw("siedzi przy stole");
						}
						else if (stan[u] == 3){
							printw("je\t\t");
						}
						else if (stan[u] == 4){
							printw("oddklada sztucce");
						}
						printw("\t\t%.2f s", progres[u]);
						printw("\t %.2f s", glod[u]);
						attroff(COLOR_PAIR(2));
					}
				}
				
				Sleep(250);
				refresh();
				clear();
				i++;

				
				for (int j = 0; j < NUMBER_OF_PHILOSOPHERS; j++){
					if (stan[j] != 3){
						glod[j] = glod[j] + 0.25;
					}
					else
					{
						glod[j] = 0;
					}
				}

				
				if (fin){

					break;
				}

			}

			

			refresh();
			clear();
			endwin();
			

			
			
			printf("Trwa zamykanie watkow ...");

			pthread_join(cyk, NULL);

			for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
				pthread_join(philosophers[i], NULL);
			}
			

			sem_destroy(&waiter);
			for (int i = 0; i < NUMBER_OF_PHILOSOPHERS; ++i) {
				sem_destroy(&fork[i]);
			}


			//int a;
			//a = getchar();
			
		}
		else
		{
		printw("Twoja Konsolka nie obsluguje kolorow. :/ ");
		}
	
	return 0;
}