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
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "config.c"

void main(){
	//variabili
	int counter = 0;
	char input[50];
	bool faction;
	bool control = true; //variabile booleana usata per memorizzare l'esito di un'azione
	
	int launchLongitude;
	int launchLatitude;
	const double rapportNorth = (double)northLenght / 90;
	const double rapportSouth = (double)southLenght / 90;
	const double rapportWest = (double)westLenght / 180;
	const double rapportEst = (double)estLenght / 180;
	
	const int sovietLenght = maxSovietLenght - minSovietLenght;
	const int sovietHight = maxSovietHight - minSovietHight;
	
	const int americanLenght = maxAmericanLenght - minAmericanLenght;
	const int americanHight = maxAmericanHight - minAmericanHight;
	
	int lineSovietBunker[sovietBunkerNumber - 1];
	int columnSovietBunker[sovietBunkerNumber - 1];
	
	int lineAmericanBunker[sovietBunkerNumber - 1];
	int columnAmericanBunker[sovietBunkerNumber - 1];
	/*il resto delle variabili sono prelevate da config.c*/
	
	//scelta della fazione
	factionASCII();
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
	
	//inizializzazione posizione bunker
	srand(time(NULL));
	while(counter < sovietBunkerNumber){
		columnSovietBunker[counter] = minSovietLenght + (rand() % sovietLenght);
		lineSovietBunker[counter] = minSovietHight + (rand() % sovietHight);
		if(faction){
			worldASCII[lineSovietBunker[counter]][columnSovietBunker[counter]] = bunkerChar;
		}
		counter++;
	}
	counter = 0;
	while(counter < americanBunkerNumber){
		columnAmericanBunker[counter] = minAmericanLenght + (rand() % americanLenght);
		lineAmericanBunker[counter] = minAmericanHight + (rand() % americanHight);
		if(!faction){
			worldASCII[lineAmericanBunker[counter]][columnAmericanBunker[counter]] = bunkerChar;
		}
		counter++;
	}
	
	//lancio dei missili nucleari
	while(true){
		//stampo la mappa
		counter = 0;
		while(counter < worldASCIIHight){
			printf("%s", &worldASCII[counter]);
			counter++;
		}
		printf("UNITED-STATES: %d - SOVIET-UNION: %d\n", americanBunkerNumber, sovietBunkerNumber);
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
		
		//controllo se hanno beccato qualcosa
		counter = 0;
		while(counter < americanBunkerNumber){
			if(columnAmericanBunker[counter] == launchLatitude){
				if(lineAmericanBunker[counter] == launchLongitude){
					americanBunkerNumber--;
					columnAmericanBunker[counter] = 0xFFFF;
					lineAmericanBunker[counter] = 0xFFFF;
				}
			}
			counter++;
		}
		counter = 0;
		while(counter < sovietBunkerNumber){
			if(columnSovietBunker[counter] == launchLatitude){
				if(lineSovietBunker[counter] == launchLongitude){
					sovietBunkerNumber--;
					columnSovietBunker[counter] = 0xFFFF;
					lineSovietBunker[counter] = 0xFFFF;
				}
			}
			counter++;
		}
		
		//metto un carattere che rappresenta il cratere della bomba
		worldASCII[launchLongitude][launchLatitude] = bombChar;
		
		//turno del robot
		printf("ENEMY SHIFT\n");
		if(!faction){
			launchLatitude = minAmericanLenght + (rand() % americanLenght);
			launchLongitude =  minAmericanHight + (rand() % americanHight);
			counter = 0;
			while(counter < americanBunkerNumber){
				if(columnAmericanBunker[counter] == launchLatitude){
					if(lineAmericanBunker[counter] == launchLongitude){
						americanBunkerNumber--;
						columnAmericanBunker[counter] = 0xFFFF;
						lineAmericanBunker[counter] = 0xFFFF;
					}
				}
				counter++;
			}
		} else {
			launchLatitude = minSovietLenght + (rand() % sovietLenght);
			launchLongitude = minSovietHight + (rand() % sovietHight);
			counter = 0;
			while(counter < sovietBunkerNumber){
				if(columnSovietBunker[counter] == launchLatitude){
					if(lineSovietBunker[counter] == launchLongitude){
						sovietBunkerNumber--;
						columnSovietBunker[counter] = 0xFFFF;
						lineSovietBunker[counter] = 0xFFFF;
					}
				}
				counter++;
			}
		}
		worldASCII[launchLongitude][launchLatitude] = bombChar;
		if(sovietBunkerNumber == 0){
			if(faction){
				ASCIIbomb();
				printf("LOOSER!\n");
				exit(0);
			} else {
				ASCIIbomb();
				printf("WINNER!\n");
				exit(0);
			}
		}else if(americanBunkerNumber == 0){
			if(faction){
				ASCIIbomb();
				printf("WINNER!\n");
				exit(0);
			} else {
				ASCIIbomb();
				printf("LOOSER!\n");
				exit(0);
			}
		}
	}
}
