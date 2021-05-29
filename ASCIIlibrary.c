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

#include <string.h>
#include <stdio.h>

void printASCII(int lineLenght, char ASCII[]){
	int counter = 0;
	int lineCounter = 1;
	while(counter < strlen(ASCII)){
		putchar(ASCII[counter]);
		if(lineCounter == lineLenght){
			printf("\n");
			lineCounter = 0;
		}
		counter++;
		lineCounter++;
	}
}

int selectASCII(int lineLenght, int line, int column){
	int zone = lineLenght * line + column;
	return zone;
}

void ASCIIbomb(){
	printf("				               ____\n");
	printf("                     __,-~~/~    `---.\n");
	printf("                   _/_,---(      ,    )\n");
	printf("               __ /        <    /   )  \\___\n");
	printf("- ------===;;;'====------------------===;;;===----- -  -\n");
	printf("                  \\/  ~\"~\"~\"~\"~\"~\\~\"~)~\"/\n");
	printf("                  (_ (   \\  (     >    \\)\n");
	printf("                   \\_( _ <         >_>'\n");
	printf("                      ~ `-i' ::>|--\"\n");
	printf("                          I;|.|.|\n");
	printf("                         <|i::|i|`.\n");
	printf("                        (` ^'\"`-' \")\n");
}
