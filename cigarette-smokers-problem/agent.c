#include "main.h"

// Agent process

void putOnTheTable(int item1, int item2) {
	table[0] = item1;
	table[1] = item2;
	printf("Agent puts: %s and %s on the table\n", materials[item1], materials[item2]);
}

void *agent(void *a) {
	int i=0;
	
	while(i++<DELIVERIES) {
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