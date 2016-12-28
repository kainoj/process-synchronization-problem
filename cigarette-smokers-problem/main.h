#ifndef _MAIN_
#define _MAIN_

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TOBACCO 0
#define MATCHES	1
#define PAPER   2

#define SMOKINGTIME 2 // in seconds
#define WARRNINGS 7
#define DELIVERIES 10

sem_t TobaccoAndPaper;
sem_t PaperAndMatches;
sem_t MatchesAndTobacco;
sem_t Delivery;

short table[2];

void *smoker(void *_ownedMaterial);
void rollNsmoke();
void warn();

void *agent(void *a);
void putOnTheTable(int item1, int item2);

extern const char *materials[];
extern const char *warrnings[];

#define COLOR_RED     "\x1b[31m"
#define COLOR_RESET   "\x1b[0m"

#endif