#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function will ask the user to Provide the license plate number which they want to Depart from the system
* If that matches and currently Parked only then The system can Let the user Go. Otherwise the system will show them whats wrong
*
* @param[in] Vehicle License Plate Number
*
* @return it will return 1 if the Vehicle can successfully depart from the system
*/

int DepartureOFVehicle()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		char key[20];
		printf("Enter License Plate to Search: "); scanf("%s", &key);
		bool found = false;
		bool hasMonthlyPass = false;
		bool alreadydeparted = false;
		bool isparked = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				found = true;
				if (strcmp(ptr->c.status, "Departed") == 0)
				{
					alreadydeparted = true;
					if (strcmp(ptr->c.montlyPass, "Yes") == 0)
					{
						hasMonthlyPass = true;
					}
				}
				if (strcmp(ptr->c.status, "Parked") == 0)
				{
					isparked = true;
					if (strcmp(ptr->c.montlyPass, "Yes") == 0)
					{
						hasMonthlyPass = true;
					}
					break;
				}
			}
			ptr = ptr->next;
		}
		if (found == false)
		{
			printf("Error ! Vehicle not found.\n");

			return 0;
		}
		if (alreadydeparted == true && isparked == false)
		{
			printf("Error ! Vehicle already departed.\n");
		}
		if (alreadydeparted == false && isparked == true)
		{
			if (hasMonthlyPass == true)
			{
				printf("This User has a Mothly Pass.\n");
				time(&ptr->c.exitTime);
				strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
				int len = strlen(ptr->c.storeExit);
				ptr->c.storeExit[len - 1] = '\0';
				double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
				seconds = seconds / 60;//3600 for hours
				ptr->c.totalTime = seconds;
				printf("Total Time %.2f Minutes.\n", seconds);
				ptr->c.price = 0.0;
				printf("Total Price (Monthly Pass Active): %.2f \n", ptr->c.price);
				strcpy(ptr->c.status, "Departed");
				printf("Vehicle Departed Successfully.\n");
			}
			else if (hasMonthlyPass == false)
			{
				printf("This User has Simple membership.\n");
				time(&ptr->c.exitTime);
				strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
				int len = strlen(ptr->c.storeExit);
				ptr->c.storeExit[len - 1] = '\0';
				double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
				seconds = seconds / 60;//3600 for hours
				ptr->c.totalTime = seconds;
				printf("Total Time %.2f Minutes.\n", seconds);
				ptr->c.price = seconds * hour;
				printf("Please pay %.2f $ before leaving.\n", ptr->c.price);
				strcpy(ptr->c.status, "Departed");
				printf("Vehicle Departed Successfully.\n");
			}

			return 1;
		}
	}
}
