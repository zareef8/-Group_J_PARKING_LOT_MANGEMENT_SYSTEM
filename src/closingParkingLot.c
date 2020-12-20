#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function will forcefully depart all Vehicles for System Exit
* and Records the Exit time for Every Parked Car
*
*
* @param[in] There is no Input for this function
*
* @return it will return 0 If a Car was Entered but could not get counted
*/

int closingParkingLot()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}
	else
	{
		bool found = false;
		bool hasMonthlyPass = false;
		struct node *ptr = head;
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.status, "Parked") == 0)
			{
				found = true;
				if (strcmp(ptr->c.montlyPass, "Yes") == 0)
				{
					time(&ptr->c.exitTime);
					strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
					int len = strlen(ptr->c.storeExit);
					ptr->c.storeExit[len - 1] = '\0';
					double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
					seconds = seconds / 60;//3600 for hours
					ptr->c.totalTime = seconds;
					ptr->c.price = 0.0;
					strcpy(ptr->c.status, "Departed");
				}
				else
				{
					time(&ptr->c.exitTime);
					strcpy(ptr->c.storeExit, ctime(&ptr->c.exitTime));
					int len = strlen(ptr->c.storeExit);
					ptr->c.storeExit[len - 1] = '\0';
					double seconds = difftime(ptr->c.exitTime, ptr->c.entryTime);
					seconds = seconds / 60;//3600 for hours
					ptr->c.totalTime = seconds;
					ptr->c.price = seconds * hour;
					strcpy(ptr->c.status, "Departed");
				}
			}
			ptr = ptr->next;

		}
		if (found == false)
		{
			printf("There were no parked vehicles.Closing Parking Lot.\n");

            return 0;
		}
		else
		{
			printf("All Vehicles departed from Parking lot.\n");
		}
	}
}
