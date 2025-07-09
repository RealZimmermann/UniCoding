#pragma warning (disable: 4996)
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*void aufgabe1a() {
	FILE* fp;																						//Filepointer
	int zeichen;																					//Für zeichenweises Lesen

	if ((fp = fopen("test.txt", "rt")) == 0) {														//Test ob Datei überhaupt vorhanden ist
		printf("Die Datei ist nicht vorhanden");
		return 0;
	}

	//Zeichenweises Lesen
	printf("--- Zeichenweises Lesen ---\n");
	while ((zeichen = fgetc(fp)) != EOF) {															//EOF steht für End of File
		fputc(zeichen, stdout);
	}

	fclose(fp);
	return 1;
}

void aufgabe1b() {
	FILE* fp;																						//Filepointer
	char line[1024];																				//Für zeilenweises Lesen

	if ((fp = fopen("test.txt", "rt")) == 0) {														//Test ob Datei überhaupt vorhanden ist
		printf("Die Datei ist nicht vorhanden");
		return 0;
	}

	//Zeilenweises Lesen
	printf("\n\n--- Zeilenweises Lesen ---\n");
	while (fgets(line, 1024, fp) != 0) {
		fputs(line, stdout);																		//oder printf(line);
	}

	fclose(fp);
	return 1;
}

void aufgabe3() {
	FILE* fp;																						//Filepointer
	int c;
	char fn[20];																					//Filename
	int characters = 0;
	int words = 1;
	int lines = 1;

	printf("Welche Datei soll geöffnet werden?\n");
	scanf("%99s", &fn);

	if ((fp = fopen(fn, "rt")) == 0) {																//Test ob Datei überhaupt vorhanden ist
		printf("Die Datei existiert nicht\n");
		return 0;
	}

	while ((c = fgetc(fp)) != EOF) {																//EOF steht für End of File
		fputc(c, stdout);																			//oder printf("%c", c);
		characters++;
		switch (c) {
		case '\n': lines++;																			// Trennzeichen
		case '\t':
		case ' ': characters++;
		case ',':
		case '.':
		case ';':
			if (!weflag) words++;
			weflag = 1;
			break;
		default: weflag = 0;
		}
	}

	if (weflag) word--;
	printf("\n\nStatistik: %d Zeichen, %d Worte, %d Zeilen", &characters, &word, &line);

	fclose(fp);
	return 1;
}*/

int main() {
	int a;
	bool check;
	printf("Willkommen zum Soduko-Spiel\n\n");
	printf("Welches Soduko-Spiel wollen Sie laden?\n");
	printf("1 - Einfache Stufe\n");
	printf("2 - Mittlere Stufe\n");
	printf("3 - Schwere Stufe\n");
	do {
		scanf("%d", &a);
		switch (a) {
		case 1:
			printf("1");
			break;
		case 2:
			printf("1");
			break;
		case 3:
			printf("1");
			break;
		default:
			check = false;
		}
	} while (check == false);
}
