#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details This will show past 30 days Vehicles information. Any entry before 30 days
* will not be counted here
*
* @param[in] No Input from user
*
* @return it will return 1 for a Proper display of Past 30 Days info otherwise it returns 0
*/

int past30Days()
{
	if (head == NULL)
	{
		printf("Database is empty.\n");
		return 0;
	}
	else
	{
		time_t rawtime;
		struct tm *info;
		time(&rawtime);
		info = localtime(&rawtime);
		int key = info->tm_yday;
		int count = 0;
		struct node*ptr;
		ptr = head;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if ((key - ptr->c.yearDay) <= 30)
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
			printf("No Vehicles came in past 30 Days.\n");
		}

		return 1;
	}
}
