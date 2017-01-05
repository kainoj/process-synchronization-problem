#ifndef _MAIN_
#define _MAIN_


#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <time.h> 

#define TOBACCO 0
#define MATCHES	1	
#define PAPER   2

#define SMOKINGTIME 2 // in seconds
#define WARRNINGS 7
#define DELIVERIES 10

typedef struct Data {
	sem_t TobaccoAndPaper;
	sem_t PaperAndMatches;
	sem_t MatchesAndTobacco;
	sem_t Delivery;
	short table[2];
} Data;

Data *d;

void smoker(int _ownedMaterial, Data *shrd_data);
void rollNsmoke(Data *shrd_data);
void warn();

void agent(Data *shrd_data);
void putOnTheTable(int item1, int item2, Data *shrd_data);

extern const char *materials[];
extern const char *warrnings[];

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

#endif