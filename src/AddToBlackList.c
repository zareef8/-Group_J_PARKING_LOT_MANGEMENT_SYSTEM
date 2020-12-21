#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function will add The License plate to the black list
* If the data is found in the system.
* User needs to be in the parking Space at least one time to active this features
*
* @param[in] Driver License Plate
*
* @return it will return 1 if the Vehicel is Blacklisted
*/

int AddToBlackList()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		char key[20];
		printf("Enter License Plate : "); scanf("%s", &key);
		bool found = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				found = true;
				printf("Data found.\n");
				strcpy(ptr->c.blacListed, "Yes");
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Data not found.\n");

			return 0;
		}
		else

			printf("Vehicle Black Listed.\n");
			return 1;
	}
}
