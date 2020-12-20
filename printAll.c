#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<time.h>
#include <math.h>
#include "../include/main_header.h"

/** @details This function will print all the information stored in a text file and from RealTime operation
* It will Print Drivers Name, License Plate Number, Parking Status, Entry and Exit time from system and Fees
*
* @param[in] This function wont take any input from User rather it it read from the text file
*
* @return it will return 1 if it can print properly otherwise It will return 0
*/


int printAll()
{
	struct node *ptr = head;
	int count = 0;
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10s|%-15s|%-15s|%-10s\n", "       Name", "  License Plate", "  Status", "     Entry Time", "     Exit Time", "Total Time", "  Monthly Pass", "  Black Listed", "  Price");
	printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	while (ptr != NULL)
	{
		count++;
		printf("%-20s|%-15s|%-10s|%-30s|%-30s|%-10.2f|%-15s|%-15s|%-.2f $\n", ptr->c.name, ptr->c.licensePlate, ptr->c.status, ptr->c.storeEntry, ptr->c.storeExit, ptr->c.totalTime, ptr->c.montlyPass,
			ptr->c.blacListed, ptr->c.price);
		printf("----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		ptr = ptr->next;
	}
	if (count !=0)
	{
		return 1;
	}
	if (count == 0)
	{
		printf("No Vehicles exist in database.\n");
		return 0;
	}
}
