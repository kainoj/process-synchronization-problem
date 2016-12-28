#include "main.h"

// Smoker process

void rollNsmoke() {
	int item1 = table[0];
	int item2 = table[1];
	printf("I got %s and %s. Rolling and smoking...\n", materials[item1], materials[item2]);
	warn();
	sleep(SMOKINGTIME);
}


void *smoker(void *_ownedMaterial) {
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


void warn() {
	printf(COLOR_RED);
	printf("\t%s\n", warrnings[rand()%WARRNINGS]);
	printf(COLOR_RESET);
}

/*
	https://en.m.wikipedia.org/wiki/Tobacco_packaging_warning_messages#United_Kingdom
*/



const char *warrnings[] = {
	"Smoking kills.",
	"Smoking causes fatal lung cancer.",
	"Smoking seriously harms you and others around you.",
	"Smokers die younger.",
	"Smoking is highly addictive, don't start.",
	"Smoking may reduce the blood flow and cause impotence.",
	"Smoking can cause a slow and painful death."
};