/*
            88         
            88         
            88         
 ,adPPYba,  88   ,d8   
a8"     "8a 88 ,a8"    
8b       d8 8888[      
"8a,   ,a8" 88`"Yba,   
 `"YbbdP"'  88   `Y8a
*/

#include <stdio.h>
#include <stdbool.h>
#include "ASCIIlibrary.c"
#include "config.c"

void main(){
	//variabili
	char input[50];
	bool faction;
	bool control = true; //variabile booleana usata per memorizzare l'esito di un'azione
	
	int launchLongitude;
	int launchLatitude;
	const double rapportNorth = (double)northLenght / 90;
	const double rapportSouth = (double)southLenght / 90;
	const double rapportWest = (double)westLenght / 180;
	const double rapportEst = (double)estLenght / 180;
	/*il resto delle variabili sono prelevate da config.c*/
	
	//scelta della fazione
	printASCII(factionASCIILenght, factionASCII);
	while(control == true){
		printf("Select a faction: ");
		scanf("%s", &input);
		if(strncmp("UNITED-STATES", input, 13) == 0){
			control = false;
			faction = false;
		}else if(strncmp("SOVIET-UNION", input, 12) == 0){
			control = false;
			faction = true;
		}else{
			printf("Faction %s don't exist.\n", input);
		}
	}
	
	//
	while(true){
		printASCII(worldASCIILenght, worldASCII);
		printf("longitude(+N, -S): ");
		scanf("%d", &launchLongitude);
		printf("latitude(+W, -E): ");
		scanf("%d", &launchLatitude);
		if(launchLongitude >= 0){
			launchLongitude = topBorderLenght + (northLenght - (int)(rapportNorth * launchLongitude + 0.5)) - 1;
		} else {
			launchLongitude = topBorderLenght + (int)(rapportSouth * -(launchLongitude) + 0.5) + northLenght - 1;
		}
		if(launchLatitude >= 0){
			launchLatitude = leftBorderLenght + (westLenght - (int)(rapportWest * launchLatitude + 0.5));
		} else {
			launchLatitude = leftBorderLenght + (int)(rapportEst * -(launchLatitude) + 0.5) + westLenght;
		}
		worldASCII[selectASCII(worldASCIILenght, launchLongitude, launchLatitude)] = bombChar;
	}
}
