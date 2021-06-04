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
#include <stdlib.h>
#include <string.h>
#include "config.c"
;
void main(){
	//variabili
	int counter = 0; //contatore di cicli
	char input[50]; //variabile per chiedere input
	bool faction; //variabile per memorizzare la fazione
	bool control = true; //variabile booleana usata per memorizzare l'esito di un'azione
	
	int launchLongitude; //longitudine verso cui sarà lanciato il missile
	int launchLatitude; //latitudine verso cui sarà lanciato il missile
	const double rapportNorth = (double)northLenght / 90; //un grado Nord in proporzione alla mappa
	const double rapportSouth = (double)southLenght / 90; //un grado Sud in proporzione alla mappa
	const double rapportWest = (double)westLenght / 180; //un grado Ovest in proporzione alla mappa
	const double rapportEst = (double)estLenght / 180; //un grado Est in proporzione alla mappa
	
	const int sovietLenght = maxSovietLenght - minSovietLenght; //lunghezza regione sovietica
	const int sovietHight = maxSovietHight - minSovietHight; //altezza regione sovietica
	
	const int americanLenght = maxAmericanLenght - minAmericanLenght; //lunghezza regione americana
	const int americanHight = maxAmericanHight - minAmericanHight; //altezza regione americana
	
	int lineSovietBunker[sovietBunkerNumber - 1]; //array per memorizzare le linee in cui sono posizionati i bunker sovietici
	int columnSovietBunker[sovietBunkerNumber - 1]; //array per memorizzare le colonne in cui sono posizionati i bunker sovietici
	
	int lineAmericanBunker[americanBunkerNumber - 1]; //array per memorizzare le linee in cui sono posizionati i bunker americani
	int columnAmericanBunker[americanBunkerNumber - 1]; //array per memorizzare le colonne in cui sono posizionati i bunker americani
	/*il resto delle variabili sono prelevate da config.c*/
	
	//scelta della fazione
	factionASCII(); //printaggio immagine fazioni
	while(control == true){
		//inserimento input
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
	
	//inizializzazione di rand()
	srand(time(NULL));
	
	//assegnazione posizione bunker
	while(counter < sovietBunkerNumber){ //ciclo di posizionamento bunker sovietici
		columnSovietBunker[counter] = minSovietLenght + (rand() % sovietLenght); //numero colonna
		lineSovietBunker[counter] = minSovietHight + (rand() % sovietHight); //numero riga
		if(faction){ //evidenzio i bunker se sono della mia fazione
			worldASCII[lineSovietBunker[counter]][columnSovietBunker[counter]] = bunkerChar;
		}
		counter++;
	}
	counter = 0;
	while(counter < americanBunkerNumber){ //ciclo di posizionamento bunker americani
		columnAmericanBunker[counter] = minAmericanLenght + (rand() % americanLenght); //numero colonna
		lineAmericanBunker[counter] = minAmericanHight + (rand() % americanHight); //numero riga
		if(!faction){ //evidenzio i bunker se sono della mia fazione
			worldASCII[lineAmericanBunker[counter]][columnAmericanBunker[counter]] = bunkerChar;
		}
		counter++;
	}
	
	//lancio dei missili nucleari
	printWorld();
	while(true){
		//turno del giocatore
		printf("YOUR SHIFT\n");
		printf("UNITED-STATES: %d - SOVIET-UNION: %d\n", americanBunkerNumber, sovietBunkerNumber);
		//input longitudine di lancio
		printf("longitude(+N, -S): ");
		scanf("%d", &launchLongitude);
		//input latitudine di lancio
		printf("latitude(+W, -E): ");
		scanf("%d", &launchLatitude);
		
		//conversione delle coordinate in numeri di righe e colonne
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
		
		if(!faction){
			printMissile(americanBunkerNumber, lineAmericanBunker, columnAmericanBunker, launchLatitude, launchLongitude, americanMissileChar);
		} else {
			printMissile(sovietBunkerNumber, lineSovietBunker, columnSovietBunker, launchLatitude, launchLongitude, sovietMissileChar);
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
		if(faction){
			printMissile(americanBunkerNumber, lineAmericanBunker, columnAmericanBunker, launchLatitude, launchLongitude, americanMissileChar);
		} else {
			printMissile(sovietBunkerNumber, lineSovietBunker, columnSovietBunker, launchLatitude, launchLongitude, sovietMissileChar);
		}
		
		//verifico se qualcuno ha vinto o perso
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

void printWorld(){
	int counter = 0;
	while(counter <= worldASCIIHight){
		printf("%s", &worldASCII[counter]);
		counter++;
	}
}

void printMissile(int bunkerNumber, int lineBunker[], int columnBunker[], int launchLatitude, int launchLongitude, char missileChar){
	double direction;
	int columnDifference;
	int lineDifference;
	int lineCounter = 0;
	int columnCounter = 0;
	char conservChar;
	int bunker = rand() % (bunkerNumber - 1); //prelievo di un bunker a caso
	
	//controllo che non sia distrutto
	while(lineBunker[bunker] == 0xFFFF){
		bunker = rand() % (bunkerNumber - 1);
	}
	
	//calcolo dello spostamento necessario
	columnDifference = launchLatitude - columnBunker[bunker];
	lineDifference = launchLongitude - lineBunker[bunker];
	
	//se la distanza che bisogna percorrere sulle ascisse è maggiore di quella delle ordinate allora aumento gradualmente le ascisse, se no faccio il contrario
	if(abs(columnDifference) > abs(lineDifference)){
		direction = (double)lineDifference / columnDifference; //valore per cui moltiplicare la linea relativa alla colonna
		while(columnCounter != columnDifference){
			lineCounter = lineBunker[bunker] + (int)(direction * columnCounter + 0.5);
			conservChar = worldASCII[lineCounter][columnCounter + columnBunker[bunker]];
			worldASCII[lineCounter][columnCounter + columnBunker[bunker]] = missileChar;
			printWorld();
			worldASCII[lineCounter][columnCounter + columnBunker[bunker]] = conservChar;
			if(columnDifference < 0){
				columnCounter--;
			}else{
				columnCounter++;
			}
			nanosleep((const struct timespec[]){{0, timeSleep}}, NULL);
		}
	} else {
		direction = (double)columnDifference / lineDifference;
		while(lineCounter != lineDifference){
			columnCounter = columnBunker[bunker] + (int)(direction * lineCounter + 0.5);
			conservChar = worldASCII[lineCounter + lineBunker[bunker]][columnCounter];
			worldASCII[lineCounter + lineBunker[bunker]][columnCounter] = missileChar;
			printWorld();
			worldASCII[lineCounter + lineBunker[bunker]][columnCounter] = conservChar;
			if(lineDifference < 0){
				lineCounter--;
			}else{
				lineCounter++;
			}
			nanosleep((const struct timespec[]){{0, timeSleep}}, NULL);
		}
	}
}
