#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This Function will remove a Car from the BlackList record
* If The Provided Information matches then the car can be removed only
*
* @param[in] Drivers License plate Plate
*
* @return it will return 1 if the Vehicle is successfully removed from the system otherwise it
* returns 0
*/

int RemoveFromBlackList()
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
		bool bfound = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				printf("Data found.\n"); found = true;
				if (strcmp(ptr->c.blacListed, "No") == 0)
				{
					printf("Error ! This vehicle is not Black Listed.\n"); bfound = true; break;
				}
				else
				{
					strcpy(ptr->c.blacListed, "No");
				}
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Data not found.\n");
			return 0;
		}
		else if (bfound == false)
			printf("Vehicle Removed from Black List.\n");
			return 1;
	}
}
