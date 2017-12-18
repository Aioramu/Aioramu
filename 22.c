#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tur {
	int c;
	int maxC;
	int* line;
} Cell;

int tFunction(Cell* cell,char* state) {

		if(!strcmp(state,"movl")) {
			if(cell->c > 0)
				cell->c--;
			else
				return 2;
		}
		if(!strcmp(state,"movr")) {
			if(cell->c >= cell->maxC) {
				cell->maxC++;
				cell->line = realloc(cell->line,cell->maxC);
				cell->line[cell->maxC] = 0;
			}
			cell->c++;

		}
		if(!strcmp(state,"inc")) {
			if(cell->line[cell->c] == 255) {
				cell->line[cell->c] = 0;
				return 1;
			}
			cell->line[cell->c] = (cell->line[cell->c] + 1)%256;
		}
		if(!strcmp(state,"dec")) {
			if(cell->line[cell->c] == 0) {
				return 1;
			}
			else
				cell->line[cell->c] -= 1;
		}

		if(!strcmp(state,"print")) {
			printf("%d\n",cell->line[cell->c]);
		}
		if(!strcmp(state,"printc")) {
			putchar(cell->line[cell->c]);
			putchar('\n');
		}
		if(!strcmp(state,"get")) {
			scanf("%d",(&(cell->line[cell->c])));
			if(cell->line[cell->c] > 255)
			{
				cell->line[cell->c] = 0;
				return 1;
			}

		}
		return 0;

}

int mainTFunc(Cell* cell, FILE* fp)
{

	char state[100];
	int outError;
	int loop_start;


	while (fscanf(fp,"%s",state) != EOF)
	{
		char spam[255];
		if(state[0] == '*')
		{
			fgets(spam,255,fp);
		}
		outError = tFunction(cell,state);

		if(!strcmp(state,"begin"))
		{
			loop_start = ftell(fp);
			while(fscanf(fp,"%s",state) != EOF && outError != 2)
			{
				if(!strcmp(state,"end") && cell->line[cell->c] == 0)
					break;
				else if(!strcmp(state,"end"))
				{
					fseek(fp,loop_start,SEEK_SET);
					continue;
				}

				if(cell->line[cell->c] == 0)
				{
					do
					{
						fscanf(fp,"%s",state);
					} while(strcmp(state,"end"));
					break;
				}
				else
					outError = tFunction(cell,state);
			}
		}

		if(outError == 1)
			printf("Error occured");

		if(outError == 2)
			return 1;

	}
	return 0;
}


int main(int argc, char** argv) {

	Cell out_Alphabet = {.c = 0, .maxC = 254, .line = (int*)malloc(255*sizeof(int))};
	int lineError;
	int i;
	for(i = 0; i < 255; i++) {
		out_Alphabet.line[i] = 0;
	}
	FILE *Erras = fopen(argv[1], "r");
	    char a[102];
	fgets(a,100,Erras);
	lineError = mainTFunc(&out_Alphabet,Erras);

	if(lineError == 1) {
		printf("Uncorrect action with tape");
		return 1;
	}

	return 0;
}
