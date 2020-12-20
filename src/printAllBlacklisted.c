#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details This function will print All the blacklisted Vehicles from the system
* If that blacklisted information fould from the file then it will print all of them
*
* @param[in] There is no Input for this function
*
* @return it will return 0 if the file is not found otherwise it will return 1
*/


int printAllBlacklisted()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		struct node *ptr = head;
		int count = 0;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.blacListed, "Yes") == 0)
			{
				count++;
				printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
					ptr->c.blacListed, ptr->c.price);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			}
			ptr = ptr->next;
		}
		if (count == 0)
		{
			printf("No Black listed Vehicles exist in database.\n");
		}
		return 1;
	}
}
