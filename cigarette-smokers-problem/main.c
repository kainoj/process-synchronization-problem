#include "main.h"

/*
	Przemysław Joniak
	Systemy Operacyjne
	2016/2017 IIUwr

	W rozwiązaniu użyto wątków.
	
	Napisz w języku C z użyciem semaforów program synchronizujący procesy.
	Objaśnij cel (założenia) danej synchronizacji oraz udokumentuj zarów-
	no program, jak i sposób jego testowania. Jako problem do rozwiązania
	możesz obrać któryś z kilkunastu klasycznych problemów synchronizacji,
	skorzystać z licznych zadań	tego typu prezentowanych w Sieci lub obmyślić
	własne (wyżej punktowane).
*/
const char *materials[] = { "tobacco", "matches", "paper"};


int main() {
	srand(time(NULL));

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
	
	if(pthread_create(&SmokerWithTobacco, NULL, smoker, (void *)tobacco)) {
		printf("Error creating thread\n"); exit(1);
	}
	if(pthread_create(&SmokerWithMatches, NULL, smoker, (void*)matches)) {
		printf("Error creating thread\n"); exit(1);
	}
	if(pthread_create(&SmokerWithPaper, NULL, smoker, (void*)paper)) {
		printf("Error creating thread\n"); exit(1);
	}
	if(pthread_create(&Agent, NULL, agent, NULL)) {
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

	return 0;
}