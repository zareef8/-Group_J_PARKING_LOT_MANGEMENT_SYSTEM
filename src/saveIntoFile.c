#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details It will save all the unsaved information to the data.txt file for future recall of the system
* if no information the it will show database is empty
*
* @param[in] there is no input from the user
*
* @return it will return 1 for a successfull Save into data.txt otherwise it will return 0
*/

int saveIntoFile()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		FILE*fptr;
		fptr = fopen("data.txt", "w");
		struct node *ptr = head;
		while (ptr != NULL)
		{
			fprintf(fptr, "%s\n", ptr->c.name);
			fprintf(fptr, "%s\n", ptr->c.licensePlate);
			fprintf(fptr, "%s\n", ptr->c.status);
			fprintf(fptr, "%s\n", ptr->c.storeEntry);
			fprintf(fptr, "%s\n", ptr->c.storeExit);
			fprintf(fptr, "%s\n", ptr->c.montlyPass);
			fprintf(fptr, "%s\n", ptr->c.blacListed);
			fprintf(fptr, "%.2lf\n", ptr->c.price);
			fprintf(fptr, "%.2lf\n", ptr->c.totalTime);
			fprintf(fptr, "%d\n", ptr->c.yearDay);

			ptr = ptr->next;
		}
		fclose(fptr);

		return 1;
	}
}
