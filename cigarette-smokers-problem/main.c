#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/*
	Napisz w języku C z użyciem semaforów program synchronizujący procesy.
	Objaśnij cel (założenia) danej synchronizacji oraz udokumentuj zarów-
	no program, jak i sposób jego testowania. Jako problem do rozwiązania
	możesz obrać któryś z kilkunastu klasycznych problemów synchronizacji,
	skorzystać z licznych zadań	tego typu prezentowanych w Sieci lub obmyślić
	własne (wyżej punktowane).
*/

#define TOBACCO 0
#define MATCHES	1
#define PAPER   2

#define SMOKINGTIME 1 // in seconds

const char *materials[] = { "tobacco", "matches", "paper"};

sem_t TobaccoAndPaper;
sem_t PaperAndMatches;
sem_t MatchesAndTobacco;
sem_t Delivery;

short table[2];

void rollNsmoke() {
	int item1 = table[0];
	int item2 = table[1];
	printf("I got %s and %s. Rolling and smoking...\n\n", materials[item1], materials[item2]);
	sleep(SMOKINGTIME);
}

void *smoke(void *_ownedMaterial) {
	int material = *( (int *) _ownedMaterial );

	while(1) {
	switch(material) {
		case 0:
			sem_wait(&PaperAndMatches);
			printf("i'm waiting for: matches and paper\n");
			rollNsmoke();
			sem_post(&Delivery);
			break;
		case 1:
			sem_wait(&TobaccoAndPaper);
			printf("i'm waiting for: tobacco and paper \n");
			rollNsmoke();
			sem_post(&Delivery);
			break;
		case 2:
			sem_wait(&MatchesAndTobacco);
			printf("i'm waiting for: tobacco and matches \n");
			rollNsmoke();
			sem_post(&Delivery);
			break;
	}
	printf("\n");
	}

	return NULL;
}

void putOnTheTable(int item1, int item2) {
	table[0] = item1;
	table[1] = item2;
	printf("Agent put: %s and %s on the table\n", materials[item1], materials[item2]);
}

void *deliver(void *a) {
	int i=0;
	
	while(++i<5) {
		sem_wait(&Delivery);
		switch(rand()%3) {
			case 0:
				putOnTheTable(MATCHES, PAPER);
				sem_post(&PaperAndMatches);
				break;
			case 1:
				putOnTheTable(TOBACCO, PAPER);
				sem_post(&TobaccoAndPaper);
				break;
			case 2:
				putOnTheTable(TOBACCO, MATCHES);
				sem_post(&MatchesAndTobacco);
				break;
		}	
	}
	return NULL;
}


int main() {
	srand(time(NULL));

	printf("Smoking kills.\n");

	pthread_t SmokerWithTobacco;
	pthread_t SmokerWithPaper;
	pthread_t SmokerWithMatches;
	pthread_t Agent;

	sem_init(&TobaccoAndPaper,   0, 0);
	sem_init(&PaperAndMatches,   0, 0);
	sem_init(&MatchesAndTobacco, 0, 0);
	sem_init(&Delivery, 0, 1);

	int *tobacco = malloc(sizeof(*tobacco)); 
	int *matches = malloc(sizeof(*matches));
	int *paper = malloc(sizeof(*paper));

	*tobacco = TOBACCO;
	*matches = MATCHES;
	*paper   = PAPER;
	
	if(pthread_create(&SmokerWithTobacco, NULL, smoke, (void *)tobacco)) {
		printf("Error creating thread\n"); exit(1);
	}
	if(pthread_create(&SmokerWithMatches, NULL, smoke, (void*)matches)) {
		printf("Error creating thread\n"); exit(1);
	}
	if(pthread_create(&SmokerWithPaper, NULL, smoke, (void*)paper)) {
		printf("Error creating thread\n"); exit(1);
	}
	if(pthread_create(&Agent, NULL, deliver, NULL)) {
		printf("Error creating thread\n"); exit(1);
	}


	if(pthread_join(SmokerWithTobacco, NULL)) {
		printf("Error joining thread\n"); exit(1);
	}
	if(pthread_join(SmokerWithMatches, NULL)) {
		printf("Error joining thread\n"); exit(1);
	}
	if(pthread_join(SmokerWithPaper, NULL)) {
		printf("Error joining thread\n"); exit(1);
	}
	if(pthread_join(Agent, NULL)) {
		printf("Error joining thread\n"); exit(1);
	}

	free(tobacco);
	free(matches);
	free(paper);

	printf("Smoking causes lung cancer.\n", );
	return 0;
}