#include "main.h"

// Agent process

void putOnTheTable(int item1, int item2, Data *shrd_data) {
	shrd_data->table[0] = item1;
	shrd_data->table[1] = item2;
	printf("Agent puts: %s and %s on the table\n", materials[item1], materials[item2]);
}

void agent(Data *shrd_data) {
	int i=0;
	
	while(i++<DELIVERIES) {
		sem_wait(&shrd_data->Delivery);
		switch(rand()%3) {
			case 0:
				putOnTheTable(MATCHES, PAPER, shrd_data);
				sem_post(&shrd_data->PaperAndMatches);
				break;
			case 1:
				putOnTheTable(TOBACCO, PAPER, shrd_data);
				sem_post(&shrd_data->TobaccoAndPaper);
				break;
			case 2:
				putOnTheTable(TOBACCO, MATCHES, shrd_data);
				sem_post(&shrd_data->MatchesAndTobacco);
				break;
		}	
	}
}