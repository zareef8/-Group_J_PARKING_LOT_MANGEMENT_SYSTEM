#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"


/** @details This will take the License plate number from User and Displays all entries for that Specific Vehicle
* If that matches the information from real-time entry and from the saved text file
*
* @param[in] Drivers License Plate
*
* @return it will return 1 if the information found otherwise it will return 0
*/


int SearchByLicensePlate()
{
    int data_found=0;
	if (head == NULL)
	{
		printf("Database is empty.\n");
	}

	else
	{
		char key[20];
		printf("Enter License Plate to search: "); scanf("%s", &key);
		bool found = false;
		struct node *ptr = head;
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		while (ptr != NULL)
		{
			if (strcmp(ptr->c.licensePlate, key) == 0)
			{
				found = true;
				printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
					ptr->c.blacListed, ptr->c.price);
				printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				data_found++;

			}
			ptr = ptr->next;
		}
		if(data_found>0)
        {
            return 1;
        }

		if (found == false)
		{
			printf("Vehicles not Found in database.\n");
			return 0;
		}
	}
}
