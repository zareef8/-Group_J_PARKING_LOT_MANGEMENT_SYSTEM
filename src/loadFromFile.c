#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details This will load data from the Text file. Name of the text file is data.txt.
* if the file can not be opened then it will show Error! File not opened to let the user know
*
* @param[in] No input for this function
*
* @return it will return 1 if the data could be loaded successfully otherwise
* if the file not found it will return 0
*/


int loadFromFile()
{
	FILE *fptr1;
	if ((fptr1 = fopen("data.txt", "r")) == NULL)
	{
		printf("Error! File not opened.");
		return 0;
		exit(1);
	}
	char line[40]; double prc = 0; double ttl = 0; bool found = false; int len;
	while (fgets(line, sizeof(line), fptr1))
	{
		struct node *link = (struct node*) malloc(sizeof(struct node));
		len = strlen(line);
		line[len - 1] = '\0';
		strcpy(link->c.name, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.licensePlate, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.status, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.storeEntry, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.storeExit, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.montlyPass, line);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; strcpy(link->c.blacListed, line);
		char *eptr;
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; link->c.price = strtod(line, &eptr);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; link->c.totalTime = strtod(line, &eptr);
		fgets(line, sizeof(line), fptr1); len = strlen(line);
		line[len - 1] = '\0'; link->c.yearDay = atoi(line);
		link->next = head;
		head = link;
	}
	fclose(fptr1);
	printf("Data Loaded from File Successfully.\n");
	return 1;
}
