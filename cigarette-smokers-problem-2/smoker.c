#include "main.h"

// Smoker process

void rollNsmoke(Data *shrd_data) {
	int item1 = shrd_data->table[0];
	int item2 = shrd_data->table[1];
	printf("I got %s and %s. Rolling and smoking...\n", materials[item1], materials[item2]);
	warn();
	sleep(SMOKINGTIME);
}


void smoker(int _ownedMaterial, Data *shrd_data) {
	int material = _ownedMaterial;

	printf("Hello, I got %s\n", materials[material]);

	while(1) {
	switch(material) {
		case 0:
			sem_wait(&shrd_data->PaperAndMatches);
			printf("i'm waiting for: matches and paper\n");			
			rollNsmoke(shrd_data);
			sem_post(&shrd_data->Delivery);
			break;
		case 1:
			sem_wait(&shrd_data->TobaccoAndPaper);
			printf("i'm waiting for: tobacco and paper \n");
			rollNsmoke(shrd_data);
			sem_post(&shrd_data->Delivery);
			break;
		case 2:			
			sem_wait(&shrd_data->MatchesAndTobacco);
			printf("i'm waiting for: tobacco and matches \n");
			rollNsmoke(shrd_data);
			sem_post(&shrd_data->Delivery);
			break;
	}
	printf("\n");
	}
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