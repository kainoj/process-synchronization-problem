#include "main.h"

/*
	Przemysław Joniak
	Systemy Operacyje
	2016/2017 IIUWr 

	W rozwiązaniu użyto procesów.
	
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
	Data *shrd_data = mmap( NULL , sizeof( Data ) , PROT_READ | PROT_WRITE , MAP_SHARED | MAP_ANONYMOUS , -1 , 0 );

	shrd_data->table[0]= 6969;
	
	printf("datasize = %d\n", sizeof(Data) );

	sem_init(&shrd_data->TobaccoAndPaper,   1, 0);
	sem_init(&shrd_data->PaperAndMatches,   1, 0);
	sem_init(&shrd_data->MatchesAndTobacco, 1, 0);
	sem_init(&shrd_data->Delivery, 1, 1);

	if( fork() == 0 ) {
		smoker(TOBACCO, shrd_data);
		return 0;
	}
	if( fork() == 0 ) {
		smoker(PAPER, shrd_data);
	}
	if( fork() == 0 ) {
		smoker(MATCHES, shrd_data);
	}

	agent(shrd_data);

	return 0;
}